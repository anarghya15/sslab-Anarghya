/*
==============================================================================================================================
Name : handsonprog33.c
Author : H Anarghya
Description : Write a program to communicate between two machines using socket.
Date: 10th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./client
Connected to server at 127.0.0.1:12345
Enter a message to send to the server: Hello
Server Response: Hello
==============================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "172.16.145.92" // Replace with the server's IP address
#define SERVER_PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in server_addr, client_addr;
    char message[1024];
    char response[1024];
    socklen_t addr_len = sizeof(client_addr);

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
     

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
    

    printf("Connected to server at %s:%d\n", SERVER_IP, SERVER_PORT);
    int client_port = getsockname(client_socket, (struct sockaddr*)&client_addr, &addr_len);
    printf("Client Port = %d\n", ntohs(client_addr.sin_port));
    
    // Send data to the server
    printf("Enter a message to send to the server: ");
    fgets(message, sizeof(message), stdin);

    send(client_socket, message, strlen(message), 0);

    // Receive and display the response from the server
    recv(client_socket, response, sizeof(response), 0);
    printf("Server Response: %s\n", response);

    // Close the client socket
    close(client_socket);

    return 0;
}

