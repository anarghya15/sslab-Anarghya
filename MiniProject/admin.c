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
    printf("Number: %d\n", no);
    lseek(fd, (no-1)*sizeof(admin), SEEK_SET);
    read(fd, &cur_admin, sizeof(cur_admin));
    close(fd);
    if(strcmp(cur_admin.adminId, admin.adminId) == 0 && strcmp(cur_admin.password, admin.password) == 0) return true;
    else return false;
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
        write(fd, details, sizeof(*details));
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
        write(fd, details, sizeof(*details));
        close(fd);
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
        write(fd, details, sizeof(*details));
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
    lock.l_start = (roll_no-1)*sizeof(cur_student);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (roll_no-1)*sizeof(cur_student), SEEK_SET);
    read(fd, &cur_student, sizeof(cur_student));
    
    if(cur_student.isActivated == true){
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, lock);
        close(fd);
        return false;
    }
    cur_student.isActivated = true;
    
    lseek(fd, -1*sizeof(cur_student), SEEK_CUR);
    write(fd, &cur_student, sizeof(cur_student));
    
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
    lock.l_start = (roll_no-1)*sizeof(cur_student);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (roll_no-1)*sizeof(cur_student), SEEK_SET);
    read(fd, &cur_student, sizeof(cur_student));
    
    if(cur_student.isActivated == false){
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, lock);
        close(fd);
        return false;
    }
    cur_student.isActivated = false;
    
    lseek(fd, -1*sizeof(cur_student), SEEK_CUR);
    write(fd, &cur_student, sizeof(cur_student));
    
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);
    return true;
}

bool modifyStudentDetails(char student_id[], char name[], int age, char email[]){
    int i, roll_no, cur_roll_no;
    struct student_details cur_student;
    struct flock lock;
    int fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDWR|O_APPEND);
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
    lock.l_start = (roll_no-1)*sizeof(cur_student);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (roll_no-1)*sizeof(cur_student), SEEK_SET);
    read(fd, &cur_student, sizeof(cur_student));

    strcpy(cur_student.name, name);
    cur_student.age = age;
    strcpy(cur_student.email, email);
    
    lseek(fd, -1*sizeof(cur_student), SEEK_CUR);
    write(fd, &cur_student, sizeof(cur_student));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);
    return true;
}

bool modifyFacultyDetails(char id[], char name[], char email[], char dept[]){
    int i, no, cur_no;
    struct faculty_details cur_faculty;
    struct flock lock;
    int fd = open("/home/dell/sslab/MiniProject/faculty.txt", O_RDWR|O_APPEND);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(id, "F%d", &no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = -1*sizeof(struct faculty_details);
    lock.l_len = sizeof(struct faculty_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, -1*sizeof(struct faculty_details), SEEK_END);
    read(fd, &cur_faculty, sizeof(struct faculty_details));
    sscanf(cur_faculty.facultyId, "F%d", &cur_no);
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    if(no > cur_no){
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (no-1)*sizeof(cur_faculty);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (no-1)*sizeof(struct faculty_details), SEEK_SET);
    read(fd, &cur_faculty, sizeof(struct faculty_details));

    strcpy(cur_faculty.name, name);
    strcpy(cur_faculty.email, email);
    strcpy(cur_faculty.department, dept);
    
    lseek(fd, -1*sizeof(cur_faculty), SEEK_CUR);
    write(fd, &cur_faculty, sizeof(cur_faculty));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    close(fd);
    return true;
}

/*int main(){
    char *id;
    //struct admin_details ad = {"A01", "password"};
    struct student_details sd = {"", "Anarghya", 24, "h.anarghya@iiitb.ac.in", ""};
    //struct faculty_details fd = {"", "Faculty2", "f2@iiitb.ac.in", "", "CSE"};
    struct student_details sd1 = {"MT001"};
    //struct faculty_details sd = {"F02"};
    //addStudent(&sd);
    //addFaculty(&fd);
    
    //viewFaculty(&sd);
    //printf("New faculty id is : %s\n", fd.facultyId);
    //printf("New student id is : %s\n", sd.studentId);
    activateStudent("MT001");
    viewStudent(&sd1);
}*/


