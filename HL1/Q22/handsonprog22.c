/*
======================================================================================================================================================================
Name : handsonprog22.c
Author : H Anarghya
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
Date: 1st Sep, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ cat prog22.txt 
Line written to file by parent process
Line written to file by child process
======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd, pid;
	fd = open("prog22.txt", O_WRONLY|O_CREAT, 0666);
	if(fd == -1){
		printf("Error: could not open file\n");
	}
	else{
		pid = fork();
		if(pid){
			char buf[] = "Line written to file by parent process\n";
			write(fd, buf, sizeof(buf));
			close(fd);
		}
		else{
			char buf[] = "Line written to file by child process\n";
			write(fd, buf, sizeof(buf));
			close(fd);
		}
	}
	return 0;
}

