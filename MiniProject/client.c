#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "menu.h"
#include "structures.h"

#define SERVER_IP "172.16.145.92" // Replace with the server's IP address
#define SERVER_PORT 8080

void handle_admin(int client_socket){
    int choice, age;
    char toContinue;
    struct student_details student;
    struct faculty_details faculty;
    char response[1000], id[6];
    do{
        printf("%s", ADMIN_MENU);
        scanf("%d", &choice);
        switch(choice){
            case 1:{
                printf("Enter student name: ");
                scanf("%[^\n]", student.name);
                printf("Enter student age: ");
                scanf("%d", student.age);
                printf("Enter student email: ");
                scanf("%[^\n]", student.email);
                send(client_socket, &student, sizeof(student), 0);
                recv(client_socket, response, sizeof(response), 0);
                break;
            }
            case 2:{
                printf("Enter faculty name: ");
                scanf("%[^\n]", faculty.name);
                printf("Enter faculty email: ");
                scanf("%[^\n]", faculty.email);
                printf("Enter faculty department: ");
                scanf("%[^\n]", faculty.department);
                send(client_socket, &faculty, sizeof(faculty), 0);
                recv(client_socket, response, sizeof(response), 0);
                break;
            }
            case 3:{
                printf("Enter student id: ");
                scanf("%[^\n]", id);
                id[5] = '\0';
                send(client_socket, &id, sizeof(id), 0);
                recv(client_socket, response, sizeof(response), 0);
                break;
            }
            case 4: {
                printf("Enter faculty id: ");
                scanf("%[^\n]", id);
                id[3] = '\0';
                send(client_socket, &id, sizeof(id), 0);
                recv(client_socket, response, sizeof(response), 0);
                break;
            }
            case 5: {
                printf("Enter student id: ");
                scanf("%[^\n]", id);
                id[5] = '\0';
                send(client_socket, &id, sizeof(id), 0);
                recv(client_socket, response, sizeof(response), 0);
                break;
            }
            case 6: {
                printf("Enter student id: ");
                scanf("%[^\n]", id);
                id[5] = '\0';
                send(client_socket, &id, sizeof(id), 0);
                recv(client_socket, response, sizeof(response), 0);
                break;
            }
            case 7:{
                printf("Enter student id: ");
                scanf("%[^\n]", student.studentId);
                student.studentId[5] = '\0';
                printf("Enter student name: ");
                scanf("%[^\n]", student.name);
                printf("Enter student age: ");
                scanf("%d", student.age);
                printf("Enter student email: ");
                scanf("%[^\n]", student.email);
                send(client_socket, &student, sizeof(student), 0);
                recv(client_socket, response, sizeof(response), 0);
                break;
            }
            case 8:{
                printf("Enter faculty id: ");
                scanf("%[^\n]", faculty.facultyId);
                printf("Enter faculty name: ");
                scanf("%[^\n]", faculty.name);
                printf("Enter faculty email: ");
                scanf("%[^\n]", faculty.email);
                printf("Enter faculty department: ");
                scanf("%[^\n]", faculty.department);
                send(client_socket, &faculty, sizeof(faculty), 0);
                recv(client_socket, response, sizeof(response), 0);
                break;
            }
            case 9:{
                printf("Thank you for using Academia!\n");
                exit(0);
            }
        }

        
        printf("%s\n", response);
        printf("Do you want to perform any more operations?[Y/N]: ");
        scanf("%c", toContinue);
    }while(toContinue == 'Y');    

}

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