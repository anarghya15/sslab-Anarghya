#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include "structures.h"
#include "faculty.h"

int compare_time_desc(const void *a, const void *b) {
    struct enrolment_details *recordA = (struct enrolment_details *)a;
    struct enrolment_details *recordB = (struct enrolment_details *)b;

    if (recordA->enrolmentTime > recordB->enrolmentTime) return -1;
    if (recordA->enrolmentTime < recordB->enrolmentTime) return 1;
    return 0;
}

bool validateFaculty(struct faculty_details faculty){
    int fd, no;
    struct faculty_details cur_faculty;
    printf("Inside validate faculty function\n");
    fd = open("/home/dell/sslab/MiniProject/faculty.txt", O_RDONLY);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(faculty.facultyId, "F%d", &no);
    lseek(fd, (no-1)*sizeof(faculty), SEEK_SET);
    read(fd, &cur_faculty, sizeof(cur_faculty));
    close(fd);
    if(strcmp(cur_faculty.facultyId, faculty.facultyId) == 0 && strcmp(cur_faculty.password, faculty.password) == 0) return true;
    else return false;
}

bool addCourse(char fid[], struct course_details *details){
    struct course_details cur_course;
    struct student_details s;
    int i, fd, fd2;
    struct flock lock;
    char filepath[100];
    struct enrolment_details enrol = {false};
    fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDWR|O_APPEND|O_CREAT, 0666);
    if(fd == -1){
        perror("open failed");
    }
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);
    int cur_pos = lseek(fd, -1*sizeof(struct student_details), SEEK_END);
    if(cur_pos == -1){
        strcpy(details->courseId, "C001");
        strcpy(details->facultyId, fid);
        details->available_seats = details->total_seats;
        details->isActive = true;
        write(fd, details, sizeof(struct course_details));
        close(fd);
        sprintf(filepath, "/home/dell/sslab/MiniProject/courses/%s.txt", details->courseId);
        fd = open(filepath, O_RDWR|O_CREAT, 0666);
        fd2 = open("/home/dell/sslab/MiniProject/faculty.txt", O_RDONLY);
        int no;
        int cur_pos = lseek(fd, -1*sizeof(struct student_details), SEEK_END);
        read(fd2, &s, sizeof(struct student_details));
        if(cur_pos != -1){
            sscanf(s.studentId, "MT%d", &no);
            for(i=0;i<no;i++){
                enrol.id = i+1;
                write(fd, &enrol, sizeof(struct enrolment_details));
            }
        }        
        close(fd);
        close(fd2);
        return true;
        
    }
    else{
        int no;
        read(fd, &cur_course, sizeof(struct course_details));
        sscanf(cur_course.courseId, "C%d", &no);
        //int no = atoi(roll_no);
        no++;
        if(no < 10){
            sprintf(details->courseId, "C00%d", no);
        }
        else if (no > 10 && no < 100){
            sprintf(details->courseId, "C0%d", no);
        }
        else {
            sprintf(details->courseId, "C%d", no);
        }
        strcpy(details->facultyId, fid);
        details->available_seats = details->total_seats;
        details->isActive = true;
        write(fd, details, sizeof(struct student_details));
        
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, lock);
        close(fd);

        sprintf(filepath, "/home/dell/sslab/MiniProject/courses/%s.txt", details->courseId);
        fd = open(filepath, O_RDWR|O_CREAT, 0666);
        fd2 = open("/home/dell/sslab/MiniProject/student.txt", O_RDONLY);
        int cur_pos = lseek(fd, -1*sizeof(struct student_details), SEEK_END);
        read(fd2, &s, sizeof(struct student_details));
        if(cur_pos != -1){
            sscanf(s.studentId, "MT%d", &no);
            for(i=0;i<no;i++){
                enrol.id = i+1;
                write(fd, &enrol, sizeof(struct enrolment_details));
            }
        }        
        close(fd);
        close(fd2);
        return true;                
    }

}

bool viewActiveCourses(char fid[], struct course_details *details){
    int fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDONLY);
    if (fd == -1) {
		perror("open failed\n");
	}   
    struct course_details course;
    int num_matches = 0;
    while (read(fd, &course, sizeof(struct course_details)) > 0) {
        if (strcmp(course.facultyId, fid) == 0 && course.isActive == true) {
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
    return true;
}

bool viewRemovedCourses(char fid[], struct course_details *details){
    int fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDONLY);
    if (fd == -1) {
		perror("open failed\n");
	}   
    struct course_details course;
    int num_matches = 0;
    while (read(fd, &course, sizeof(struct course_details)) > 0) {
        if (strcmp(course.facultyId, fid) == 0 && course.isActive == false) {
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
    return true;
}

bool removeCourse(char cid[], char fid[]){
    int i, c_no, cur_no;
    struct flock lock;
    struct course_details course;
    int fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(cid, "C%d", &c_no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = -1*sizeof(struct course_details);
    lock.l_len = sizeof(struct course_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);

    lseek(fd, -1*sizeof(struct course_details), SEEK_END);
    read(fd, &course, sizeof(struct course_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    sscanf(course.courseId, "C%d", &cur_no);
    if(c_no > cur_no || strcmp(course.facultyId, fid) != 0){
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (c_no-1)*sizeof(struct course_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (c_no-1)*sizeof(struct course_details), SEEK_SET);
    read(fd, &course, sizeof(struct course_details));
    
    course.isActive = false;
    
    lseek(fd, -1*sizeof(struct course_details), SEEK_CUR);
    write(fd, &course, sizeof(struct course_details));
    
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);
    return true;
}

bool activateCourse(char cid[], char fid[]){
    int i, c_no, cur_no;
    struct flock lock;
    struct course_details course;
    int fd = open("/home/dell/sslab/MiniProject/course.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(cid, "C%d", &c_no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = -1*sizeof(struct course_details);
    lock.l_len = sizeof(struct course_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);

    lseek(fd, -1*sizeof(struct course_details), SEEK_END);
    read(fd, &course, sizeof(struct course_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    sscanf(course.courseId, "C%d", &cur_no);
    if(c_no > cur_no || strcmp(course.facultyId, fid) != 0){
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (c_no-1)*sizeof(struct course_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (c_no-1)*sizeof(struct course_details), SEEK_SET);
    read(fd, &course, sizeof(struct course_details));
    
    course.isActive = true;
    
    lseek(fd, -1*sizeof(struct course_details), SEEK_CUR);
    write(fd, &course, sizeof(struct course_details));
    
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);
    return true;
}

bool modifyCourse(char cid[], char name[], int seats, char fid[]){
    int i, c_no, cur_no;
    struct course_details course, new_course_details;
    struct flock lock;
    int fd = open("/home/dell/sslab/MiniProject/student.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(cid, "C%d", &c_no);

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = -1*sizeof(struct course_details);
    lock.l_len = sizeof(struct course_details);
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, -1*sizeof(struct course_details), SEEK_END);
    read(fd, &course, sizeof(struct course_details));
    sscanf(course.courseId, "C%d", &cur_no);
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    if(c_no > cur_no || strcmp(course.facultyId, fid) != 0){
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (c_no-1)*sizeof(struct course_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (c_no-1)*sizeof(struct course_details), SEEK_SET);
    read(fd, &course, sizeof(struct course_details));
    strcpy(new_course_details.courseId, cid);
    strcpy(new_course_details.name, name);
    new_course_details.total_seats = seats;

    if(seats > course.total_seats){
        new_course_details.available_seats = course.available_seats + (seats-course.total_seats);
    }
    else{
        int diff = course.total_seats - seats;
        new_course_details.available_seats = course.available_seats - diff;
        if(new_course_details.available_seats < 0) {
            removeEnrolments(cid, abs(new_course_details.available_seats));
            new_course_details.available_seats = 0;
        }
    }

    strcpy(new_course_details.facultyId, course.facultyId);
    new_course_details.isActive = course.isActive;

    lseek(fd, -1*sizeof(struct course_details), SEEK_CUR);
    write(fd, &new_course_details, sizeof(struct course_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);

    //TODO Remove extra enrolments
    return true;
    
}

bool changePassword(char fid[], char newpwd[]){
    int fd, no;
    struct faculty_details cur_faculty;
    struct flock lock;
    fd = open("/home/dell/sslab/MiniProject/faculty.txt", O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    sscanf(fid, "F%d", &no);

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (no-1)*sizeof(struct faculty_details);
    fcntl(fd, F_SETLKW, lock);
    lseek(fd, (no-1)*sizeof(struct faculty_details), SEEK_SET);
    read(fd, &cur_faculty, sizeof(struct faculty_details));

    strcpy(cur_faculty.password, newpwd);
    lseek(fd, -1*sizeof(struct faculty_details), SEEK_CUR);
    write(fd, &cur_faculty, sizeof(struct faculty_details));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);

    close(fd);
    return true;
}

void removeEnrolments(char cid[], int count){
    int fd, i=0;
    char filepath[100];
    struct flock lock;
    struct enrolment_details *records, record;
    size_t num_records = 0;
    sprintf(filepath, "/home/dell/sslab/MiniProject/course/%s.txt", cid);
    fd = open(filepath, O_RDWR);
    if(fd == -1){
        perror("open failed");
    }
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    fcntl(fd, F_SETLKW, lock);

    while(read(fd, &record, sizeof(struct enrolment_details)) > 0){
        records = realloc(records, (num_records + 1) * sizeof(struct enrolment_details));
        if (records == NULL) {
            perror("Memory allocation error");
            close(fd);
            free(records);
            return;
        }
        records[num_records] = record;
        num_records++;
    }

    qsort(records, num_records, sizeof(struct enrolment_details), compare_time_desc);
    while(i<count){
        int no = records[i].id;
        lseek(fd, (no-1)*sizeof(struct enrolment_details), SEEK_SET);
        read(fd, &record, sizeof(struct enrolment_details));
        if(record.isEnrolled == false) continue;
        record.isEnrolled = false;
        lseek(fd, (no-1)*sizeof(struct enrolment_details), SEEK_SET);
        write(fd, &record, sizeof(struct enrolment_details));
        i++;
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, lock);
    close(fd);


}
