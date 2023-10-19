#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "menu.h"
#include "structures.h"
#include "admin.h"
#include "faculty.h"
#include "student.h"

#define PORT 8081
#define MAX_CONNECTIONS 5

void *handle_client(void *client_socket);
void handle_admin_ops(int client_socket);
void handle_faculty_ops(int, char[]);
void handle_student_ops(int, char[]);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t thread_id;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a client connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }
        printf("Accepted connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, (void *)&client_socket) != 0) {
            perror("Thread creation failed");
            close(client_socket);
        }
    }
    close(server_socket);
    return 0;
}

void handle_admin_ops(int client_socket) {
    char buffer[1024], id[6], client_data[1000], ch;
    int bytes_received;
    struct admin_details admin;
    struct student_details student;
    struct faculty_details faculty;
    int choice;
    
    do{
    strcpy(client_data, ADMIN_MENU);
    send(client_socket, &client_data, strlen(client_data), 0);
    recv(client_socket, &choice, sizeof(choice), 0);
    switch(choice){
        case 1:{
            strcpy(client_data, "Enter student name: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            
            recv(client_socket, &student.name, sizeof(student.name), 0);
            
            strcpy(client_data, "Enter student age: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &student.age, sizeof(student.age), 0);
            
            strcpy(client_data, "Enter student email: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &student.email, sizeof(student.email), 0);
            
            bool opResult = addStudent(&student);
            if(opResult){
                strcpy(client_data, "Student added successfully!\n");
                sprintf(buffer, "Generated student ID: %s\n", student.studentId);
                strcat(client_data, buffer);
            }
            else{
                strcpy(client_data, "Could not add the student with given details!\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 2:{
            strcpy(client_data, "Enter faculty name: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &faculty.name, sizeof(faculty.name), 0);

            strcpy(client_data, "Enter faculty email: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &faculty.email, sizeof(faculty.email), 0);

            strcpy(client_data, "Enter faculty department: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &faculty.department, sizeof(faculty.department), 0);

            bool opResult = addFaculty(&faculty);
            if(opResult){
                strcpy(client_data, "Faculty added successfully!\n");
                sprintf(buffer, "Generated faculty ID: %s\n", faculty.facultyId);
                strcat(client_data, buffer);
            }
            else{
                strcpy(client_data, "Could not add the faculty with given details!\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 3:{
            strcpy(client_data, "Enter student id: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, student.studentId, sizeof(student.studentId), 0);
            student.studentId[5] = '\0';
            
            bool opResult = viewStudent(&student);
            if(opResult){
                strcpy(client_data, "The student details are as follows: \n");
                sprintf(buffer, "Student ID: %s\n", student.studentId);
                strcat(client_data, buffer);
                sprintf(buffer, "Student Name: %s\n", student.name);
                strcat(client_data, buffer);
                sprintf(buffer, "Student Age: %d\n", student.age);
                strcat(client_data, buffer);
                sprintf(buffer, "Student email: %s\n", student.email);
                strcat(client_data, buffer);
                sprintf(buffer, "Student is active: %s\n", student.isActivated? "True":"False");
                strcat(client_data, buffer);
            }
            else{
                strcpy(client_data, "Could not get the student details with given ID!\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 4:{
            strcpy(client_data, "Enter faculty id: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, faculty.facultyId, sizeof(faculty.facultyId), 0);
            faculty.facultyId[3] = '\0';

            bool opResult = viewFaculty(&faculty);
            if(opResult){
                strcpy(client_data, "The faculty details are as follows: \n");
                sprintf(buffer, "Faculty ID: %s\n", faculty.facultyId);
                strcat(client_data, buffer);
                sprintf(buffer, "Faculty Name: %s\n", faculty.name);
                strcat(client_data, buffer);
                sprintf(buffer, "Faculty email: %s\n", faculty.email);
                strcat(client_data, buffer);
                sprintf(buffer, "Faculty department: %s\n", faculty.department);
                strcat(client_data, buffer);
            }
            else{
                strcpy(client_data, "Could not get the faculty details with given ID!\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 5:{
            strcpy(client_data, "Enter student id: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, id, sizeof(id), 0);
            id[5] = '\0';
            bool opResult = activateStudent(id);
            if(opResult){
                //Success
                strcpy(buffer, "Student activated successfully!!\n");
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            else{
                strcpy(buffer, "Student activation failed!!\n");
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            break;
        }
        case 6:{
            strcpy(client_data, "Enter student id: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, id, sizeof(id), 0);
            id[5] = '\0';
            bool opResult = deactivateStudent(id);
            if(opResult){
                //Success
                strcpy(buffer, "Student deactivated successfully!!\n");
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            else{
                strcpy(buffer, "Student deactivation failed!!\n");
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            break;
        }
        case 7:{
            strcpy(client_data, "Enter student ID: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &student.studentId, sizeof(student.studentId), 0);
            student.studentId[5] = '\0';

            strcpy(client_data, "Enter student name: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &student.name, sizeof(student.name), 0);

            strcpy(client_data, "Enter student age: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &student.age, sizeof(student.age), 0);

            strcpy(client_data, "Enter student email: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &student.email, sizeof(student.email), 0);
            printf("Received name: %s\n", student.name);
            printf("Received age: %d\n", student.age);
            printf("Received email: %s\n", student.email);
            bool opResult = modifyStudentDetails(student.studentId, student.name, student.age, student.email);
            if(opResult){
                //Success
                strcpy(buffer, "Student modified successfully!!\n");
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            else{
                strcpy(buffer, "Student modification failed!!\n");
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            break;
        }
        case 8:{
            strcpy(client_data, "Enter faculty ID: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &faculty.facultyId, sizeof(faculty.facultyId), 0);
            student.studentId[5] = '\0';

            strcpy(client_data, "Enter faculty name: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &faculty.name, sizeof(faculty.name), 0);

            strcpy(client_data, "Enter faculty email: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &faculty.email, sizeof(faculty.email), 0);

            strcpy(client_data, "Enter faculty department: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &faculty.department, sizeof(faculty.department), 0);

            bool opResult = modifyFacultyDetails(faculty.facultyId, faculty.name, faculty.email, faculty.department);
            if(opResult){
                //Success
                strcpy(buffer, "Faculty modified successfully!!\n");
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            else{
                strcpy(buffer, "Faculty modification failed!!\n");
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            break;
        }
        case 9: {
            strcpy(buffer, "Thank you for using Academia portal!\n");
            send(client_socket, &buffer, strlen(buffer), 0);
            break;
        }
        default:{
            strcpy(buffer, "Invalid choice!\n");
            send(client_socket, &buffer, strlen(buffer), 0);
            break;
        }      
            
    } 
    if(choice == 9){
        ch='N';
        continue;
    }
    strcpy(client_data, "Do you want to perform any other operations?[Y/N]: ") ;
    send(client_socket, &client_data, strlen(client_data), 0);
    recv(client_socket, &ch, 1, 0);
    }while(ch != 'N');  
    
}

void handle_faculty_ops(int client_socket, char faculty_id[]) {
    char buffer[1024], id[6], client_data[2048], ch, pwd[100], confirm_pwd[100];
    int bytes_received, count;
    struct course_details course, *cDetails;
    cDetails = (struct course_details *)malloc(sizeof(struct course_details));
    struct faculty_details faculty;
    int choice;
    
    do{
    strcpy(client_data, FACULTY_MENU);
    send(client_socket, &client_data, strlen(client_data), 0);
    recv(client_socket, &choice, sizeof(choice), 0);
    switch(choice){
        case 1:{
            strcpy(client_data, "Enter course name: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &course.name, sizeof(course.name), 0);
            
            strcpy(client_data, "Enter the total seats: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &course.total_seats, sizeof(course.total_seats), 0);
            
            bool opResult = addCourse(faculty_id, &course);
            if(opResult){
                strcpy(client_data, "Course added successfully!\n");
                sprintf(buffer, "Generated course ID: %s\n", course.courseId);
                strcat(client_data, buffer);
            }
            else{
                strcpy(client_data, "Could not add the course with given details!\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 2:{
            bool opResult = viewActiveCourses(faculty_id, cDetails, &count);
            if(opResult){
                if(count>0){
                    int i = 0;
                    strcpy(client_data, "\nThe course details are as follows:\n");
                    while(i<count){
                        strcat(client_data, "---------------------------------------------------------------------\n");
                        sprintf(buffer, "Course ID: %s\nCourse Name: %s\nTotal Seats:%d \nAvailable seats: %d\n", cDetails[i].courseId, cDetails[i].name, cDetails[i].total_seats, cDetails[i].available_seats);
                        strcat(client_data, buffer);
                        i++;
                    }
                }
                else{
                    strcpy(client_data, "No courses to display!\n");
                }
                
                
            }
            else{
                strcpy(client_data, "Could not get the course details\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 3:{
            bool opResult = viewRemovedCourses(faculty_id, cDetails, &count);
            if(opResult){
                if(count>0){
                    int i=0;
                    strcpy(client_data, "\nThe course details are as follows:\n");
                    while(i<count){
                        strcat(client_data, "---------------------------------------------------------------------\n");
                        sprintf(buffer, "Course ID: %s\nCourse Name: %s\nTotal Seats:%d \nAvailable seats: %d\n", cDetails[i].courseId, cDetails[i].name, cDetails[i].total_seats, cDetails[i].available_seats);
                        strcat(client_data, buffer);
                        i++;
                    }
                }
                else{
                    strcpy(client_data, "No courses to display!\n");
                }
                
                
            }
            else{
                strcpy(client_data, "Could not get the course details\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 4:{
            strcpy(client_data, "Enter course id: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, id, sizeof(id), 0);
            id[4] = '\0';

            bool opResult = removeCourse(id, faculty_id);
            if(opResult){
                strcpy(client_data, "Course Removed successfully!\n");
            }
            else{
                strcpy(client_data, "Failed to remove the course, either the course ID is invalid or you are not authorized to remove the course.\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 5:{
            strcpy(client_data, "Enter course id: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, id, sizeof(id), 0);
            id[4] = '\0';

            bool opResult = activateCourse(id, faculty_id);
            if(opResult){
                strcpy(client_data, "Course re-activated successfully!\n");
            }
            else{
                strcpy(client_data, "Failed to activate the course, either the course ID is invalid or you are not authorized to remove the course.\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 6:{
            strcpy(client_data, "Enter course ID: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &course.courseId, sizeof(course.courseId), 0);
            course.courseId[4] = '\0';

            strcpy(client_data, "Enter course name: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &course.name, sizeof(course.name), 0);

            strcpy(client_data, "Enter total number of seats: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, &course.total_seats, sizeof(course.total_seats), 0);

            bool opResult = modifyCourse(course.courseId, course.name, course.total_seats, faculty_id);
            if(opResult){
                //Success
                strcpy(buffer, "Course modified successfully!!\n");
            }
            else{
                strcpy(buffer, "Failed to modify the course details, either the course ID is invalid or you are not authorized to remove the course.\n");
            }
            send(client_socket, &buffer, strlen(buffer), 0);
            break;
        }        
        case 7:{
            strcpy(client_data, "Enter new password: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            bytes_received = recv(client_socket, &pwd, sizeof(pwd), 0);
            pwd[bytes_received] = '\0';

            strcpy(client_data, "Confirm new password: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            bytes_received = recv(client_socket, &confirm_pwd, sizeof(confirm_pwd), 0);
            confirm_pwd[bytes_received] = '\0';

            
            if(strcmp(pwd, confirm_pwd) != 0){
                strcpy(buffer, "Passwords do not match, please try again!!\n");
            }
            else{
                bool opResult = changePassword(faculty_id, pwd);
                if(opResult){
                    //Success
                    strcpy(buffer, "Password changes successfully!!\n");
                }
                else{
                    strcpy(buffer, "Failed to change the password!\n");
                }
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            
            break;
        }
        case 8: {
            strcpy(buffer, "Thank you for using Academia portal!\n");
            send(client_socket, &buffer, strlen(buffer), 0);
            break;
        }
        default:{
            strcpy(buffer, "Invalid choice!\n");
            send(client_socket, &buffer, strlen(buffer), 0);
            break;
        }      
            
    } 
    if(choice == 8){
        ch='N';
        continue;
    }
    strcpy(client_data, "Do you want to perform any other operations?[Y/N]: ") ;
    send(client_socket, &client_data, strlen(client_data), 0);
    recv(client_socket, &ch, 1, 0);
    }while(ch != 'N');
}

void handle_student_ops(int client_socket, char student_id[]) {
    char buffer[1024], id[6], client_data[2048], ch, pwd[100], confirm_pwd[100], **faculty_names;
    struct course_details course, *cDetails;
    cDetails = (struct course_details*)malloc(sizeof(struct course_details));
    struct faculty_details faculty;
    int choice, count, bytes_received;
    faculty_names = (char**)malloc(100*sizeof(char));
    
    do{
    strcpy(client_data, STUDENT_MENU);
    send(client_socket, &client_data, strlen(client_data), 0);
    recv(client_socket, &choice, sizeof(choice), 0);
    switch(choice){
        case 1:{
            bool isActive = isStudentActive(student_id);
            if(!isActive){
                strcpy(client_data, "You are not authorized to perform thie operation since you are not active\n");
                send(client_socket, client_data, sizeof(client_data), 0);
                break;
            }
            bool opResult = viewCourses(cDetails, faculty_names, &count);
            if(opResult){
                if(count>0){
                    int i=0;
                    strcpy(client_data, "\nThe course details are as follows:\n");
                    while(i<count){
                        strcat(client_data, "---------------------------------------------------------------------\n");
                        sprintf(buffer, "Course ID: %s\nCourse Name: %s\nFaculty In Charge:%s \nAvailable seats: %d\n", cDetails[i].courseId, cDetails[i].name, faculty_names[i], cDetails[i].available_seats);
                        printf("Course ID: %s\nCourse Name: %s\nFaculty In Charge:%s \nAvailable seats: %d\n", cDetails[i].courseId, cDetails[i].name, faculty_names[i], cDetails[i].available_seats);
                        
                        strcat(client_data, buffer);
                        i++;
                    }
                }
                else{
                    strcpy(client_data, "No courses to display!\n");
                }               
                
            }
            else{
                strcpy(client_data, "Could not get the course details\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 2:{
            bool isActive = isStudentActive(student_id);
            if(!isActive){
                strcpy(client_data, "You are not authorized to perform thie operation since you are not active\n");
                send(client_socket, client_data, sizeof(client_data), 0);
                break;
            }
            bool opResult = viewCourses(cDetails, faculty_names, &count);
            if(opResult){
                if(count>0){
                    strcpy(client_data, "\nThe course details are as follows:\n");
                    int i = 0;
                    while(i<count){
                        strcat(client_data, "---------------------------------------------------------------------\n");
                        sprintf(buffer, "Course ID: %s\nCourse Name: %s\nFaculty In Charge:%s \nAvailable seats: %d\n", cDetails[i].courseId, cDetails[i].name, faculty_names[i], cDetails[i].available_seats);
                        strcat(client_data, buffer);
                        i++;
                    }
                }
                else{
                    strcpy(client_data, "No courses to display!\n");
                }               
                
            }
            if(count > 0){
                strcat(client_data, "Enter course id: ");
                send(client_socket, &client_data, strlen(client_data), 0);
                recv(client_socket, id, sizeof(id), 0);
                id[4] = '\0';

                opResult = enrollCourse(id, student_id);
                if(opResult){
                    strcpy(client_data, "Course enrollment successful!\n");
                }
                else{
                    strcpy(client_data, "Failed to enroll for the course, please check the course ID \n");
                }
                send(client_socket, client_data, sizeof(client_data), 0);
            }            
            break;
        }
        case 3:{
            bool isActive = isStudentActive(student_id);
            if(!isActive){
                strcpy(client_data, "You are not authorized to perform thie operation since you are not active\n");
                send(client_socket, client_data, sizeof(client_data), 0);
                break;
            }
            strcpy(client_data, "Enter course id: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            recv(client_socket, id, sizeof(id), 0);
            id[4] = '\0';

            bool opResult = dropCourse(id, student_id);
            if(opResult){
                strcpy(client_data, "Course dropped successfully!\n");
            }
            else{
                strcpy(client_data, "Failed to un enroll for the course, please check the course ID.\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }
        case 4:{
            bool isActive = isStudentActive(student_id);
            if(!isActive){
                strcpy(client_data, "You are not authorized to perform thie operation since you are not active\n");
                send(client_socket, client_data, sizeof(client_data), 0);
                break;
            }
            cDetails = (struct course_details*)malloc(sizeof(struct course_details));
            bool opResult = viewEnrolledCourses(student_id, cDetails, &count);
            if(opResult){
                strcpy(client_data, "\nThe courses are as follows:\n");
                int i=0;
                while(i<count){
                    strcat(client_data, "---------------------------------------------------------------------\n");
                    sprintf(buffer, "Course ID: %s\nCourse Name: %s\n", cDetails[i].courseId, cDetails[i].name);
                    strcat(client_data, buffer);
                    i++;
                }
                
            }
            else{
                strcpy(client_data, "Could not get the course details\n");
            }
            send(client_socket, client_data, sizeof(client_data), 0);
            break;
        }        
        case 5:{
            strcpy(client_data, "Enter new password: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            bytes_received = recv(client_socket, &pwd, sizeof(pwd), 0);
            pwd[bytes_received] = '\0';

            strcpy(client_data, "Confirm new password: ");
            send(client_socket, &client_data, strlen(client_data), 0);
            bytes_received = recv(client_socket, &confirm_pwd, sizeof(confirm_pwd), 0);
            confirm_pwd[bytes_received] = '\0';

            
            if(strcmp(pwd, confirm_pwd) != 0){
                strcpy(buffer, "Passwords do not match, please try again!!\n");
            }
            else{
                bool opResult = changePasswordStudent(student_id, pwd);
                if(opResult){
                    //Success
                    strcpy(buffer, "Password changes successfully!!\n");
                }
                else{
                    strcpy(buffer, "Failed to change the password!\n");
                }
                send(client_socket, &buffer, strlen(buffer), 0);
            }
            
            break;
        }
        case 6: {
            strcpy(buffer, "Thank you for using Academia portal!\n");
            send(client_socket, &buffer, strlen(buffer), 0);
            break;
        }
        default:{
            strcpy(buffer, "Invalid choice!\n");
            send(client_socket, &buffer, strlen(buffer), 0);
            break;
        }      
            
    } 
    if(choice == 6){
        ch='N';
        continue;
    }
    strcpy(client_data, "Do you want to perform any other operations?[Y/N]: ") ;
    send(client_socket, &client_data, strlen(client_data), 0);
    recv(client_socket, &ch, 1, 0);
    }while(ch != 'N');
}

void *handle_client(void *arg){
    int client_socket = *((int *)arg), choice, noOfTries = 0;
    bool isValidated;
    char client_data[1000], response[1000], id[6], password[100];
    struct admin_details admin;
    struct student_details student;
    struct faculty_details faculty;

    strcpy(client_data, WELCOME_MENU);
    send(client_socket, &client_data, strlen(client_data), 0);
    recv(client_socket, &choice, sizeof(choice), 0);   
    printf("Choice: %d\n", choice);

    
    switch(choice){
        case 1:{
            while(1){
                strcpy(client_data, "Enter the login ID: ");
                send(client_socket, &client_data, strlen(client_data), 0);
                recv(client_socket, admin.adminId, sizeof(admin.adminId), 0); 
                
                strcpy(client_data, "Enter the password: ");
                send(client_socket, &client_data, strlen(client_data), 0);
                recv(client_socket, admin.password, sizeof(admin.password), 0);
                printf("Password: %s\n", admin.password);

                isValidated = validateAdmin(admin);
                if(isValidated){
                    strcpy(client_data, "Login successful!! Please wait..\n\n");
                    send(client_socket, &client_data, strlen(client_data), 0);
                    noOfTries = 4;
                    sleep(5);
                    int bytes = send(client_socket, &noOfTries, sizeof(noOfTries), 0);
                    handle_admin_ops(client_socket);
                }
                else{
                    noOfTries++;
                    if(noOfTries == 3){
                        strcpy(client_data, "Exiting after 3 login attempts\n");
                        send(client_socket, &client_data, strlen(client_data), 0);
                        sleep(1);
                        send(client_socket, &noOfTries, sizeof(noOfTries), 0);
                        break;
                    }
                    else{
                        strcpy(client_data, "Invalid login ID or password, please try again!\n");
                        send(client_socket, &client_data, strlen(client_data), 0);
                        sleep(1);
                        send(client_socket, &noOfTries, sizeof(noOfTries), 0);
                    }
                }
            }
            break;
        }
        case 2:{
            while(1){
                strcpy(client_data, "Enter the login ID: ");
                send(client_socket, &client_data, strlen(client_data), 0);
                recv(client_socket, faculty.facultyId, sizeof(faculty.facultyId), 0); 

                strcpy(client_data, "Enter the password: ");
                send(client_socket, &client_data, strlen(client_data), 0);
                recv(client_socket, faculty.password, sizeof(faculty.password), 0); 
                isValidated = validateFaculty(faculty);
                if(isValidated){
                    strcpy(client_data, "Login successful!! Please wait..\n\n");
                    send(client_socket, &client_data, strlen(client_data), 0);
                    noOfTries = 4;
                    sleep(5);
                    int bytes = send(client_socket, &noOfTries, sizeof(noOfTries), 0);
                    handle_faculty_ops(client_socket, faculty.facultyId);
                }
                else{
                    noOfTries++;
                    if(noOfTries == 3){
                        strcpy(client_data, "Exiting after 3 login attempts\n");
                        send(client_socket, &client_data, strlen(client_data), 0);
                        sleep(1);
                        send(client_socket, &noOfTries, sizeof(noOfTries), 0);
                        break;
                    }
                    else{
                        strcpy(client_data, "Invalid login ID or password, please try again!\n");
                        send(client_socket, &client_data, strlen(client_data), 0);
                        sleep(1);
                        send(client_socket, &noOfTries, sizeof(noOfTries), 0);
                    }
                }
            }
            break;
        }
        case 3:{
            while(1){
                strcpy(client_data, "Enter the login ID: ");
                send(client_socket, &client_data, strlen(client_data), 0);
                recv(client_socket, student.studentId, sizeof(student.studentId), 0); 

                strcpy(client_data, "Enter the password: ");
                send(client_socket, &client_data, strlen(client_data), 0);
                recv(client_socket, student.password, sizeof(student.password), 0); 
                isValidated = validateStudent(student);
                if(isValidated){
                    strcpy(client_data, "Login successful!! Please wait..\n\n");
                    send(client_socket, &client_data, strlen(client_data), 0);
                    noOfTries = 4;
                    sleep(5);
                    int bytes = send(client_socket, &noOfTries, sizeof(noOfTries), 0);
                    handle_student_ops(client_socket, student.studentId);
                }
                else{
                    noOfTries++;
                    if(noOfTries == 3){
                        strcpy(client_data, "Exiting after 3 login attempts\n");
                        send(client_socket, &client_data, strlen(client_data), 0);
                        break;
                    }
                    else{
                        strcpy(client_data, "Invalid login ID or password, please try again!\n");
                        send(client_socket, &client_data, strlen(client_data), 0);
                        send(client_socket, &noOfTries, sizeof(noOfTries), 0);
                    }
                }
            }
            break;
        }
        default:{
            strcpy(client_data, "Invalid choice, please try again");
            send(client_socket, &client_data, strlen(client_data), 0);            
        }       
    }       
    close(client_socket);
    pthread_exit(NULL);

}