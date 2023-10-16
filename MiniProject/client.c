#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "menu.h"
#include "structures.h"

#define SERVER_IP "127.0.0.1" // Replace with the server's IP address
#define SERVER_PORT 8080

void handle_admin(int);

int main() {
    int client_socket, choice, noOfTries = 0, noOfBytes;
    struct sockaddr_in server_addr, client_addr;
    char message[1024], server_response[1024], id[6], password[100];
    socklen_t addr_len = sizeof(client_addr);
    struct admin_details admin;
    struct student_details student;
    struct faculty_details faculty;

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
    //int client_port = getsockname(client_socket, (struct sockaddr*)&client_addr, &addr_len);
    //printf("Client Port = %d\n", ntohs(client_addr.sin_port));
    
    // Send data to the server
    //printf("Enter a message to send to the server: ");
    //fgets(message, sizeof(message), stdin);      

    //send(client_socket, message, strlen(message), 0);

    // Receive and display the response from the server
    //recv(client_socket, response, sizeof(response), 0);
    //printf("Server Response: %s\n", response);

    //Get menu
    noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
    server_response[noOfBytes] = '\0';
    write(1, server_response, strlen(server_response)); 
    int tries;                
    scanf("%d", &choice);
    send(client_socket, &choice, sizeof(choice), 0);
    switch(choice){
        case 1: {
            while (1)
            {
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                read(0, id, sizeof(id));
                id[3] = '\0';
                send(client_socket, id, strlen(id), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                int x = read(0, password, sizeof(password));
                password[x-1] = '\0';
                send(client_socket, password, strlen(password), 0);

                recv(client_socket, server_response, sizeof(server_response), 0);
                write(1, server_response, strlen(server_response));
                recv(client_socket, &tries, sizeof(tries), 0);
                if(tries >=3) break;              

            }
            if(tries == 4) handle_admin(client_socket);
            break;              
        }

    }
    // Close the client socket
    close(client_socket);

    return 0;
}

void handle_admin(int client_socket){
    int noOfBytes, choice, age;
    char server_response[1000], data[1000], name[100], email[100], ch, dept[100], id[6];

    do{
        noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
        server_response[noOfBytes] = '\0';
        write(1, server_response, strlen(server_response)); 
        scanf("%d", &choice);
        send(client_socket, &choice, sizeof(choice), 0);
        switch(choice){
            case 1: {  
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &name, sizeof(name));
                name[noOfBytes-1] = '\0';
                send(client_socket, name, strlen(name), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                scanf("%d", &age);
                send(client_socket, &age, sizeof(age), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &email, sizeof(email));
                email[noOfBytes-1] = '\0';
                send(client_socket, email, strlen(email), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 

                break;
            }

            case 2: {  
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &name, sizeof(name));
                name[noOfBytes-1] = '\0';
                send(client_socket, &name, strlen(name), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &email, sizeof(email));
                email[noOfBytes-1] = '\0';
                send(client_socket, email, strlen(email), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &dept, sizeof(dept));
                dept[noOfBytes-1] = '\0'; 
                send(client_socket, dept, strlen(dept), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 

                break;
            }

            case 3: {
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &id, sizeof(id));
                id[noOfBytes-1] = '\0';
                send(client_socket, id, strlen(id), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                break;
            }

            case 4: {
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &id, sizeof(id));
                id[noOfBytes-1] = '\0';
                send(client_socket, id, strlen(id), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                break;
            }

            case 5: {
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &id, sizeof(id));
                id[noOfBytes-1] = '\0';
                send(client_socket, id, strlen(id), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                break;
            }

            case 6: {
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &id, sizeof(id));
                id[noOfBytes-1] = '\0';
                send(client_socket, id, strlen(id), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                break;
            }

            case 7: {
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &id, sizeof(id));
                id[noOfBytes-1] = '\0';
                send(client_socket, name, strlen(id), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &name, sizeof(name));
                name[noOfBytes-1] = '\0';
                send(client_socket, name, strlen(name), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                scanf("%d", &age);
                send(client_socket, &age, sizeof(age), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &email, sizeof(email));
                email[noOfBytes-1] = '\0';
                send(client_socket, email, strlen(email), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 

                break;
            }

            case 8: {
                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &id, sizeof(id));
                id[noOfBytes-1] = '\0';
                send(client_socket, name, strlen(id), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &name, sizeof(name));
                name[noOfBytes-1] = '\0';
                send(client_socket, name, strlen(name), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &email, sizeof(email));
                email[noOfBytes-1] = '\0';
                send(client_socket, email, strlen(email), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                noOfBytes = read(0, &dept, sizeof(dept));
                dept[noOfBytes-1] = '\0';
                send(client_socket, dept, strlen(dept), 0);

                noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
                server_response[noOfBytes] = '\0';
                write(1, server_response, strlen(server_response)); 
                break;
            }
        }
        noOfBytes = recv(client_socket, server_response, sizeof(server_response), 0); 
        server_response[noOfBytes] = '\0';
        write(1, server_response, strlen(server_response)); 
        noOfBytes = read(0, &ch, sizeof(ch));
        send(client_socket, &ch, sizeof(ch), 0);
    }while(ch != 'N');
}