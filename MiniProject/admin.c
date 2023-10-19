#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include "structures.h"
#include "admin.h"

bool validateAdmin(struct admin_details admin){
    int fd, no;
    struct admin_details cur_admin;
    printf("Inside validate admin function\n");
    fd = open("/home/dell/sslab/MiniProject/admin_details.txt", O_RDONLY);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(admin.adminId, "A%d", &no);
    printf("ID: %s\n", admin.adminId);
    printf("Password: %s\n", admin.password);
    lseek(fd, (no-1)*sizeof(admin), SEEK_SET);
    read(fd, &cur_admin, sizeof(cur_admin));
    close(fd);
    if(strcmp(cur_admin.adminId, admin.adminId) == 0 && strcmp(cur_admin.password, admin.password) == 0) return true;
    else return false;
}

void addStudentRecordToCourses(int id){
    struct enrolment_details enrol = {id, false};
    struct course_details course;
    char filepath[100];
    int no, i;
    int fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDWR|O_APPEND|O_CREAT, 0666);
    if(fd == -1){
        perror("open failed");
    }
    int cur_pos = lseek(fd, -1*sizeof(struct course_details), SEEK_END);
    if(cur_pos != -1){
        read(fd, &course, sizeof(struct course_details));
        close(fd);

        sscanf(course.courseId, "C%d", &no);
        for(i=1;i<=no;i++){
            sprintf(filepath, "/home/dell/sslab/MiniProject/courses/C%d.txt", i);
            int fd = open(filepath, O_RDWR|O_APPEND);
            if(fd == -1){
                perror("open failed");
            }
            write(fd, &enrol, sizeof(struct enrolment_details));
            close(fd);
        }
    
    }
    close(fd);
}

bool addStudent(struct student_details *details){
    struct student_details cur_student;
    int i;
    int fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDWR|O_APPEND|O_CREAT, 0666);
    if(fd == -1){
        perror("open failed");
    }
    int cur_pos = lseek(fd, -1*sizeof(struct student_details), SEEK_END);
    if(cur_pos == -1){
        strcpy(details->studentId, "MT001");
        strcpy(details->password, "password");
        details->isActivated = true;
        write(fd, details, sizeof(struct student_details));
        addStudentRecordToCourses(1);
        close(fd);
        return true;
        
    }
    else{
        int no;
        read(fd, &cur_student, sizeof(struct student_details));
        sscanf(cur_student.studentId, "MT%d", &no);
        //int no = atoi(roll_no);
        no++;
        if(no < 10){
            sprintf(details->studentId, "MT00%d", no);
        }
        else if (no > 10 && no < 100){
            sprintf(details->studentId, "MT0%d", no);
        }
        else {
            sprintf(details->studentId, "MT%d", no);
        }
        strcpy(details->password, "password");
        details->isActivated = true;
        write(fd, details, sizeof(struct student_details));
        close(fd);
        addStudentRecordToCourses(no);
        return true;
                
    }
    close(fd);
    return false;

}

bool viewStudent(struct student_details *details){
    struct student_details cur_student;
    int fd, i, roll_no, cur_roll_no;
    fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDONLY);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(details->studentId, "MT%d", &roll_no);
    lseek(fd, -1*sizeof(struct student_details), SEEK_END);
    read(fd, &cur_student, sizeof(struct student_details));
    sscanf(cur_student.studentId, "MT%d", &cur_roll_no);
    if(roll_no > cur_roll_no){
        return false;
    }
    lseek(fd, (roll_no-1)*sizeof(struct student_details), SEEK_SET);
    read(fd, details, sizeof(struct student_details));
    close(fd);
    return true;
}

bool addFaculty(struct faculty_details *details){
    struct faculty_details cur_faculty;
    int i;
    int fd = open("/home/dell/sslab/MiniProject/faculty.txt", O_RDWR|O_APPEND|O_CREAT, 0666);
    if(fd == -1){
        perror("open failed");
    }
    int cur_pos = lseek(fd, -1*sizeof(struct faculty_details), SEEK_END);
    if(cur_pos == -1){
        strcpy(details->facultyId, "F01");
        strcpy(details->password, "password");
        write(fd, details, sizeof(*details));
        close(fd);
        return true;
        
    }
    else{
        int no;
        read(fd, &cur_faculty, sizeof(struct faculty_details));
        sscanf(cur_faculty.facultyId, "F%d", &no);
        no++;
        if(no < 10){
            sprintf(details->facultyId, "F0%d", no);
        }
        else {
            sprintf(details->facultyId, "F%d", no);
        }
        strcpy(details->password, "password");
        write(fd, details, sizeof(struct student_details));
        close(fd);
        return true;
                
    }
    close(fd);
    return false;

}

bool viewFaculty(struct faculty_details *details){
    struct faculty_details cur_faculty;
    int fd, i, no, cur_no;
    fd = open("/home/dell/sslab/MiniProject/faculty.txt", O_RDONLY);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(details->facultyId, "F%d", &no);
    lseek(fd, -1*sizeof(struct faculty_details), SEEK_END);
    read(fd, &cur_faculty, sizeof(struct faculty_details));
    sscanf(cur_faculty.facultyId, "F%d", &cur_no);
    if(no > cur_no){
        return false;
    }
    lseek(fd, (no-1)*sizeof(struct faculty_details), SEEK_SET);
    read(fd, details, sizeof(struct faculty_details));
    close(fd);
    return true;
}

bool activateStudent(char student_id[]){
    int i, roll_no, cur_roll_no;
    struct flock lock;
    struct student_details cur_student;
    int fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(student_id, "MT%d", &roll_no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = -1*sizeof(struct student_details);
    lock.l_len = sizeof(struct student_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);

    lseek(fd, -1*sizeof(struct student_details), SEEK_END);
    read(fd, &cur_student, sizeof(struct student_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    sscanf(cur_student.studentId, "MT%d", &cur_roll_no);
    if(roll_no > cur_roll_no){
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (roll_no-1)*sizeof(struct student_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (roll_no-1)*sizeof(struct student_details), SEEK_SET);
    read(fd, &cur_student, sizeof(struct student_details));
    
    if(cur_student.isActivated == true){
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, lock);
        close(fd);
        return false;
    }
    cur_student.isActivated = true;
    
    lseek(fd, -1*sizeof(struct student_details), SEEK_CUR);
    write(fd, &cur_student, sizeof(struct student_details));
    
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);
    return true;

}

bool deactivateStudent(char student_id[]){
    int i, roll_no, cur_roll_no;
    struct flock lock;
    struct student_details cur_student;
    int fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(student_id, "MT%d", &roll_no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = -1*sizeof(struct student_details);
    lock.l_len = sizeof(struct student_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);

    lseek(fd, -1*sizeof(struct student_details), SEEK_END);
    read(fd, &cur_student, sizeof(struct student_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    sscanf(cur_student.studentId, "MT%d", &cur_roll_no);
    if(roll_no > cur_roll_no){
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (roll_no-1)*sizeof(struct student_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (roll_no-1)*sizeof(struct student_details), SEEK_SET);
    read(fd, &cur_student, sizeof(struct student_details));
    
    if(cur_student.isActivated == false){
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, lock);
        close(fd);
        return false;
    }
    cur_student.isActivated = false;
    
    lseek(fd, -1*sizeof(struct student_details), SEEK_CUR);
    write(fd, &cur_student, sizeof(struct student_details));
    
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);
    return true;
}

bool modifyStudentDetails(char student_id[], char name[], int age, char email[]){
    int i, roll_no, cur_roll_no;
    struct student_details cur_student, new_student_details;
    struct flock lock;
    int fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(student_id, "MT%d", &roll_no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = -1*sizeof(struct student_details);
    lock.l_len = sizeof(struct student_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, -1*sizeof(struct student_details), SEEK_END);
    read(fd, &cur_student, sizeof(struct student_details));
    sscanf(cur_student.studentId, "MT%d", &cur_roll_no);
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    if(roll_no > cur_roll_no){
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (roll_no-1)*sizeof(struct student_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (roll_no-1)*sizeof(struct student_details), SEEK_SET);
    read(fd, &cur_student, sizeof(struct student_details));
    strcpy(new_student_details.studentId, student_id);
    strcpy(new_student_details.name, name);
    new_student_details.age = age;
    strcpy(new_student_details.email, email);
    strcpy(new_student_details.password, cur_student.password);
    new_student_details.isActivated = cur_student.isActivated;
    
    lseek(fd, -1*sizeof(struct student_details), SEEK_CUR);
    write(fd, &new_student_details, sizeof(struct student_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);
    return true;
}

bool modifyFacultyDetails(char id[], char name[], char email[], char dept[]){
    int i, no, cur_no;
    struct faculty_details cur_faculty, new_faculty_details;
    struct flock lock;
    int fd = open("/home/dell/sslab/MiniProject/faculty.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(id, "MT%d", &no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = -1*sizeof(struct faculty_details);
    lock.l_len = sizeof(struct faculty_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, -1*sizeof(struct faculty_details), SEEK_END);
    read(fd, &cur_faculty, sizeof(struct faculty_details));
    sscanf(cur_faculty.facultyId, "MT%d", &cur_no);
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    if(no > cur_no){
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (no-1)*sizeof(struct faculty_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (no-1)*sizeof(struct faculty_details), SEEK_SET);
    read(fd, &cur_faculty, sizeof(struct faculty_details));
    strcpy(new_faculty_details.facultyId, id);
    strcpy(new_faculty_details.name, name);
    strcpy(new_faculty_details.email, email);
    strcpy(new_faculty_details.department, dept);
    strcpy(new_faculty_details.password, cur_faculty.password);
    
    lseek(fd, -1*sizeof(struct faculty_details), SEEK_CUR);
    write(fd, &new_faculty_details, sizeof(struct faculty_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);
    return true;
}

/*int main(){
    char *id, client_data[1000], buffer[500];
    //struct admin_details ad = {"A01", "password"};
    struct student_details sd = {"", "Anarghya", 24, "h.anarghya@iiitb.ac.in", ""};
    //struct faculty_details fd = {"", "Faculty2", "f2@iiitb.ac.in", "", "CSE"};
    struct student_details sd1 = {"MT001"};
    //struct faculty_details sd = {"F02"};
    addStudent(&sd);
    //addFaculty(&fd);
    
    //viewFaculty(&sd);
    //printf("New faculty id is : %s\n", fd.facultyId);
    //printf("New student id is : %s\n", sd.studentId);
    //activateStudent("MT001");
    viewStudent(&sd1);
    //modifyStudentDetails("MT001", "Anu", 23, "anu@gmail.com");
    //viewStudent(&sd1);
    strcpy(client_data, "The student details are as follows: \n");
    sprintf(buffer, "Student ID: %s\n", sd1.studentId);
    strcat(client_data, buffer);
    sprintf(buffer, "Student Name: %s\n", sd1.name);
    strcat(client_data, buffer);
    sprintf(buffer, "Student Age: %d\n", sd1.age);
    strcat(client_data, buffer);
    sprintf(buffer, "Student email: %s\n", sd1.email);
    strcat(client_data, buffer);
    sprintf(buffer, "Student is active: %s\n", sd1.isActivated? "True":"False");
    strcat(client_data, buffer);
    printf("%s\n", client_data);
}*/


