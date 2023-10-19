/*
==============================================================================================================================
Name : handsonprog33.c
Author : H Anarghya
Description : Write a program to communicate between two machines using socket.
Date: 10th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./server
Server is listening on port 12345
Accepted connection from 127.0.0.1:38110
Received: Hello
Accepted connection from 127.0.0.1:54338
Received: Hi
==============================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[1024];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; //Automatically assign IP addr of current machine

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", SERVER_PORT);

    while (1) {
        client_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Error accepting connection");
            continue;
        }

        printf("Accepted connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            perror("Error receiving data");
        } else {
            buffer[bytes_received] = '\0'; // Null-terminate the received data
            printf("Received: %s", buffer);

            send(client_socket, buffer, strlen(buffer), 0);
        }

        close(client_socket);
    }

    close(server_socket);

    return 0;
}

