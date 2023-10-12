#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include "structures.h"

char[] addStudent(struct student_details details){
    struct student_details cur_student;
    char roll_no[4];
    int i;
    int fd = open("student.txt", O_RDWR|O_APPEND|O_CREAT, 0666);
    if(fd == -1){
        perror("open failed");
    }
    int cur_pos = lseek(fd, -1*sizeof(struct student_details), SEEK_END);
    if(cur_pos == 0){
        int no_of_bytes = read(fd, &cur_student, sizeof(cur_student));
        if(no_of_bytes == 0){
            strcpy(details.studentId, "MT001");
            lseek(fd, sizeof(details), SEEK_CUR);
            write(fd, &details, sizeof(details));
        }
        else{            
            for(i=2;i<5;i++){
                roll_no[i-2] = cur_student.studentId[i];
            }
            roll_no[i-1] = '\0';
            int no = atoi(roll_no);
            no++;
            tostring(roll_no, no);
            strcpy(details.password, "password");
            //if(strlen(roll_no) == 1)
            return roll_no;
            //details.studentId = 
            //write(fd, &details, sizeof(details));
        }
        
    }
    else{
        int no_of_bytes = read(fd, &cur_student, sizeof(cur_student));
        
    }
    printf("Student created successfully!!\n");
    printf("Generated student ID is: %s\n", details.studentId);
    close(fd);

}

struct student_details viewStudent(char student_id[]){
    struct student_details cur_student;
    int fd, i;
    char roll_no[4];
    fd = open("student.txt", O_RDONLY);
    if(fd == -1){
        perror("open failed");
    }
    for(i=2;i<5;i++){
        roll_no[i-2] = student_id[i];
    }
    roll_no[i-1] = '\0';
    int no = atoi(roll_no);
    lseek(fd, (no-1)*sizeof(struct student_details), SEEK_SET);
    read(fd, &cur_student, sizeof(struct student_details));
    close(fd);
    return cur_student;
}

void addFaculty(struct faculty_details details){
    struct faculty_details cur_faculty;
    char faculty_no[3];
    int i;
    int fd = open("faculty.txt", O_RDWR|O_APPEND|O_CREAT, 0666);
    if(fd == -1){
        perror("open failed");
    }
    int cur_pos = lseek(fd, -1*sizeof(struct faculty_details), SEEK_END);
    if(cur_pos == 0){
        int no_of_bytes = read(fd, &cur_faculty, sizeof(cur_faculty));
        if(no_of_bytes == 0){
            strcpy(details.facultyId, "F01");
            lseek(fd, sizeof(details), SEEK_CUR);
            write(fd, &details, sizeof(details));
        }
        else{            
            for(i=1;i<3;i++){
                faculty_no[i-1] = cur_faculty.facultyId[i];
            }
            faculty_no[i-1] = '\0';
            int no = atoi(faculty_no);
            no++;
            tostring(faculty_no, no);
            //if(strlen(roll_no) == 1)
            printf("Faculty No is %s\n", faculty_no);
            //details.studentId = 
            //write(fd, &details, sizeof(details));
        }
        
    }
    else{
        int no_of_bytes = read(fd, &cur_faculty, sizeof(cur_faculty));
        
    }
    printf("Faculty created successfully!!\n");
    printf("Generated faculty ID is: %s\n", details.facultyId);
    close(fd);

}

struct faculty_details viewFaculty(char student_id[]){
    struct faculty_details cur_faculty;
    int fd, i;
    char faculty_no[3];
    fd = open("faculty.txt", O_RDONLY);
    if(fd == -1){
        perror("open failed");
    }
    for(i=1;i<3;i++){
        faculty_no[i-2] = student_id[i];
    }
    faculty_no[i-1] = '\0';
    int no = atoi(faculty_no);
    lseek(fd, (no-1)*sizeof(cur_faculty), SEEK_SET);
    read(fd, &cur_faculty, sizeof(cur_faculty));
    close(fd);
    return cur_faculty;
}

bool activateStudent(char student_id[]){
    int i;
    char roll_no[4];
    struct student_details cur_student;
    int fd = open("student.txt", O_RDWR|O_APPEND);
    if(fd == -1){
        perror("open failed");
    }
    for(i=2;i<5;i++){
        roll_no[i-2] = student_id[i];
    }
    roll_no[i-1] = '\0';
    int no = atoi(roll_no);
    lseek(fd, (no-1)*sizeof(cur_student), SEEK_SET);
    read(fd, &cur_student, sizeof(cur_student));
    if(cur_student.isActivated == true){
        close(fd);
        return false;
    }
    cur_student.isActivated = true;
    lseek(fd, -1*sizeof(cur_student), SEEK_CUR);
    write(fd, &cur_student, sizeof(cur_student));
    close(fd);
    return true;

}

bool deavtivateStudent(char student_id[]){
    int i;
    char roll_no[4];
    struct student_details cur_student;
    int fd = open("student.txt", O_RDWR|O_APPEND);
    if(fd == -1){
        perror("open failed");
    }
    for(i=2;i<5;i++){
        roll_no[i-2] = student_id[i];
    }
    roll_no[i-1] = '\0';
    int no = atoi(roll_no);
    lseek(fd, (no-1)*sizeof(cur_student), SEEK_SET);
    read(fd, &cur_student, sizeof(cur_student));
    if(cur_student.isActivated == false){
        close(fd);
        return false;
    }
    cur_student.isActivated = false;
    lseek(fd, -1*sizeof(cur_student), SEEK_CUR);
    write(fd, &cur_student, sizeof(cur_student));
    close(fd);
    return true;
}

void modifyStudentDetails(char id[], char name[], int age, char email[]){
    int i;
    char roll_no[4];
    struct student_details cur_student;
    int fd = open("student.txt", O_RDWR|O_APPEND);
    if(fd == -1){
        perror("open failed");
    }
    for(i=2;i<5;i++){
        roll_no[i-2] = id[i];
    }
    roll_no[i-1] = '\0';
    int no = atoi(roll_no);
    lseek(fd, (no-1)*sizeof(cur_student), SEEK_SET);
    read(fd, &cur_student, sizeof(cur_student));
    strcpy(cur_student.name, name);
    cur_student.age = age;
    strcpy(cur_student.email, email);
    lseek(fd, -1*sizeof(cur_student), SEEK_CUR);
    write(fd, &cur_student, sizeof(cur_student));
    close(fd);
}

void modifyFacultyDetails(char id[], char name[], char email[], char dept[]){
    int i;
    char faculty_no[3];
    struct faculty_details cur_faculty;
    int fd = open("faculty.txt", O_RDWR|O_APPEND);
    if(fd == -1){
        perror("open failed");
    }
    for(i=1;i<3;i++){
        faculty_no[i-2] = id[i];
    }
    faculty_no[i-1] = '\0';
    int no = atoi(faculty_no);
    lseek(fd, (no-1)*sizeof(cur_faculty), SEEK_SET);
    read(fd, &cur_faculty, sizeof(cur_faculty));
    strcpy(cur_faculty.name, name);
    strcpy(cur_faculty.email, email);
    strcpy(cur_faculty.department, dept);
    lseek(fd, -1*sizeof(cur_faculty), SEEK_CUR);
    write(fd, &cur_faculty, sizeof(cur_faculty));
    close(fd);
}


