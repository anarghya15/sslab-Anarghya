/*
==================================================================================================
Name : handsonprog19.c
Author : H Anarghya
Description : Create a FIFO file by
		a. mknod command
		b. mkfifo command
		c. use strace command to find out, which command (mknod or mkfifo) is better.
		d. mknod system call
		e. mkfifo library function
Date: 10th Oct, 2023.
===================================================================================================

===================================================================================================
Sample output:
$ mknod fifo1 p
$ ls -l
total 4
prw-rw-r-- 1 dell dell    0 Oct 10 17:59 fifo1
-rw-rw-r-- 1 dell dell 1417 Oct 10 17:49 handsonprog19.c
$ mkfifo fifo2
$ ls -l
total 4
prw-rw-r-- 1 dell dell    0 Oct 10 17:59 fifo1
prw-rw-r-- 1 dell dell    0 Oct 10 17:59 fifo2
-rw-rw-r-- 1 dell dell 1417 Oct 10 17:49 handsonprog19.c

$ ./h19
FIFO file created successfully using library call
FIFO file created successfully using mknod system call
$ ls -l
total 36
-rwxrwxr-x 1 dell dell 16096 Oct 10 18:04 19
prw-rw-r-- 1 dell dell     0 Oct 10 18:01 fifo1
prw-rw-r-- 1 dell dell     0 Oct 10 18:03 fifo2
-rwxrwxr-x 1 dell dell 16096 Oct 10 18:05 h19
-rw-rw-r-- 1 dell dell  1417 Oct 10 17:49 handsonprog19.c
prwx------ 1 dell dell     0 Oct 10 18:05 myfifofile
p--------- 1 dell dell     0 Oct 10 18:05 myfifofile1
===================================================================================================
*/

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	//Create a FIFO file using mkfifo library call
	if(mkfifo("myfifofile", S_IFIFO|S_IRWXU) == -1){
		perror("mkfifo");
	}
	else {
		printf("FIFO file created successfully using library call\n");
	}
	//Create a FIFO file using mknod system call
	if(mknod("myfifofile1", S_IFIFO, 0) == -1){
		perror("Failed to create named pipe");
	}
	else {
		printf("FIFO file created successfully using mknod system call\n");
	}
	return 0;
}
