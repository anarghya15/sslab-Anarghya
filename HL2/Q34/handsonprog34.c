/*
==============================================================================================================================
Name : handsonprog34a.c
Author : H Anarghya
Description : Write a program to create a concurrent server.
		a. use fork
		b. use pthread_create
Date: 10th Oct, 2023.
==============================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CONNECTIONS 5

void handle_client(int client_socket);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];
    int bytes_received;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            close(server_socket);
            
            while (1) {
		bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
		
		if (bytes_received <= 0) {
            		break; // Client closed the connection
        	}

		send(client_socket, buffer, bytes_received, 0);
    	    }
            close(client_socket);
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            close(client_socket); 
        }
    }

    close(server_socket);
    return 0;
}

