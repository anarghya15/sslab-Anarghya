/*
======================================================================================================================================================================
Name : handsonprog18.c
Author : H Anarghya
Description : Write a program to perform Record locking.
		a. Implement write lock
		b. Implement read lock
		Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
Date: 25th Aug, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ ./write
Enter the record number: 
2
Before locking the record for writing
Write lock acquired successfully....
Enter roll number and marks:
2
45
Record written successfully!
Enter to unlock...
======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

int main(){
	int i, fd;
	struct {
		int rollno;
		int marks;
	} db;
	struct flock fl;
    fd = open("records.txt", O_WRONLY);
    
    printf("Enter the record number: \n");
    scanf("%d", &i);
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = (i-1)*sizeof(db);
    fl.l_len = sizeof(db);
    fl.l_pid = getpid();
    printf("Before locking the record for writing\n");
    fcntl(fd, F_SETLKW, &fl);
    printf("Write lock acquired successfully....\n");
    printf("Enter roll number and marks:\n");
    scanf("%d", &db.rollno);
    scanf("%d", &db.marks);
    lseek(fd, (i-1)*sizeof(db), SEEK_SET);
    write(fd, &db, sizeof(db));
    printf("Record written successfully!\n");
    printf("Enter to unlock...\n");
    getchar();
    getchar();
    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &fl);
    printf("Finish\n");
    return 0;
}
