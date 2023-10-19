#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include "structures.h"
#include "student.h"

bool validateStudent(struct student_details student){
    int fd, no;
    struct student_details cur_student;
    printf("Inside validate student function\n");
    fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDONLY);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(student.studentId, "F%d", &no);
    lseek(fd, (no-1)*sizeof(student), SEEK_SET);
    read(fd, &cur_student, sizeof(cur_student));
    close(fd);
    if(strcmp(cur_student.studentId, student.studentId) == 0 && strcmp(cur_student.password, student.password) == 0) return true;
    else return false;
}

bool viewCourses(struct course_details *details, char **faculty_names){
    int fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDONLY);
    if (fd == -1) {
		perror("open failed\n");
	}   
    struct course_details course;
    struct faculty_details faculty;
    int num_matches = 0;
    while (read(fd, &course, sizeof(struct course_details)) > 0) {
        if (course.isActive == true && course.available_seats > 0) {
            details = realloc(details, (num_matches + 1) * sizeof(struct course_details));
            if (details == NULL) {
                perror("Memory allocation error");
                close(fd);
                free(details);
                return false;
            }
            details[num_matches] = course;
            num_matches++;
        }
    }    
    close(fd);
    faculty_names = (char**) malloc(num_matches*100);
    fd = open("/home/dell/sslab/MiniProject/faculty.txt", O_RDONLY);
    if (fd == -1) {
		perror("open failed\n");
	}
    struct course_details *temp = details;
    int i=0;
    while(temp != NULL){
        int no;
        sscanf(temp->facultyId, "C%d", &no);
        lseek(fd, (no-1)*sizeof(struct faculty_details), SEEK_SET);
        read(fd, &faculty, sizeof(struct faculty_details));
        strcpy(faculty_names[i], faculty.name);
        i++;
        temp++;
    }
    return true;
}

bool enrollCourse(char courseId[], char studentId[]){
    struct course_details course;
    int fd, fd2;
    struct flock lock;
    int c_no, s_no;
    char filepath[100];
    fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDWR);
    if (fd == -1) {
		perror("open failed\n");
	} 
    sscanf(courseId, "C%d", &c_no);

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (c_no-1)*sizeof(struct course_details);
    lock.l_len = sizeof(struct course_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);

    lseek(fd, (c_no-1)*sizeof(struct course_details), SEEK_SET);
    read(fd, &course, sizeof(struct course_details));

    sprintf(filepath, "/home/dell/sslab/MiniProject/courses/%s.txt", courseId);
    fd2 = open(filepath, O_RDWR);
    if (fd == -1) {
		perror("open failed\n");
	}

    sscanf(studentId, "MT%d", &s_no);
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (s_no-1)*sizeof(struct enrolment_details);
    lock.l_len = sizeof(struct enrolment_details);
    lock.l_pid = getpid();
    fcntl(fd2, F_SETLKW, lock);

    struct enrolment_details enrol;
    enrol.isEnrolled = true;
    time_t currentTimestamp;
    time(&currentTimestamp);
    enrol.enrolmentTime = currentTimestamp;
    write(fd2, &enrol, sizeof(struct enrolment_details));

    course.available_seats--;
    lseek(fd, (c_no-1)*sizeof(struct course_details), SEEK_SET);
    write(fd, &course, sizeof(struct course_details));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    fcntl(fd2, F_SETLK, lock);

    return true;
}

bool dropCourse(char courseId[], char studentId[]){
    struct course_details course;
    int fd, fd2;
    struct flock lock;
    int c_no, s_no;
    char filepath[100];
    fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDWR);
    if (fd == -1) {
		perror("open failed\n");
	} 
    sscanf(courseId, "C%d", &c_no);

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (c_no-1)*sizeof(struct course_details);
    lock.l_len = sizeof(struct course_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);

    lseek(fd, (c_no-1)*sizeof(struct course_details), SEEK_SET);
    read(fd, &course, sizeof(struct course_details));

    sprintf(filepath, "/home/dell/sslab/MiniProject/courses/%s.txt", courseId);
    fd2 = open(filepath, O_RDWR);
    if (fd == -1) {
		perror("open failed\n");
	}

    sscanf(studentId, "MT%d", &s_no);
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (s_no-1)*sizeof(struct enrolment_details);
    lock.l_len = sizeof(struct enrolment_details);
    lock.l_pid = getpid();
    fcntl(fd2, F_SETLKW, lock);

    struct enrolment_details enrol;
    enrol.isEnrolled = false;
    time_t currentTimestamp;
    time(&currentTimestamp);
    enrol.enrolmentTime = currentTimestamp;
    write(fd2, &enrol, sizeof(struct enrolment_details));

    course.available_seats++;
    lseek(fd, (c_no-1)*sizeof(struct course_details), SEEK_SET);
    write(fd, &course, sizeof(struct course_details));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    fcntl(fd2, F_SETLK, lock);

    return true;
}

bool viewEnrolledCourses(char sid[], struct course_details *enrolled_courses){
    int fd, no;
    struct course_details *courses, course;
    struct flock lock;
    struct enrolment_details enrolled;
    char filepath[100];
    fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDONLY);
    if (fd == -1) {
		perror("open failed\n");
	}
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);

    int num_matches = 0;
    while (read(fd, &course, sizeof(struct course_details)) > 0) {
        if (course.isActive == true) {
            courses = realloc(courses, (num_matches + 1) * sizeof(struct course_details));
            if (courses == NULL) {
                perror("Memory allocation error");
                close(fd);
                free(courses);
                return false;
            }
            courses[num_matches] = course;
            num_matches++;
        }
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);

    sscanf(sid, "MT%d", &no);
    while(courses != NULL){
        sprintf(filepath, "/home/dell/sslab/MiniProject/courses/%s.txt", courses->courseId);
        fd = open(filepath, O_RDONLY, 0666);
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (no-1)*sizeof(struct enrolment_details);
        lock.l_len = sizeof(struct enrolment_details);
        lock.l_pid = getpid();
        fcntl(fd, F_SETLKW, lock);

        lseek(fd, (no-1)*sizeof(struct enrolment_details), SEEK_SET);
        read(fd, &enrolled, sizeof(struct enrolment_details));
        num_matches = 0;
        if (enrolled.isEnrolled == true)
        {
            enrolled_courses = realloc(enrolled_courses, (num_matches + 1) * sizeof(struct course_details));
            if (enrolled_courses == NULL) {
                perror("Memory allocation error");
                close(fd);
                free(enrolled_courses);
                return false;
            }
            enrolled_courses[num_matches] = course;
            num_matches++;
        }
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, lock);
        close(fd); 
        courses++;
    }
    return true;


}

bool changePasswordStudent(char sid[], char newpwd[]){
    int fd, no;
    struct student_details cur_student;
    struct flock lock;
    fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(sid, "MT%d", &no);

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (no-1)*sizeof(struct student_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (no-1)*sizeof(struct student_details), SEEK_SET);
    read(fd, &cur_student, sizeof(struct student_details));

    strcpy(cur_student.password, newpwd);
    lseek(fd, -1*sizeof(struct student_details), SEEK_CUR);
    write(fd, &cur_student, sizeof(struct student_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    close(fd);
    return true;
}

bool isStudentActive(char sid[]){
    int fd, no;
    struct student_details cur_student;
    struct flock lock;
    fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDONLY);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(sid, "MT%d", &no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (no-1)*sizeof(struct student_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (no-1)*sizeof(struct student_details), SEEK_SET);
    read(fd, &cur_student, sizeof(struct student_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    close(fd);
    return cur_student.isActivated;
    
}