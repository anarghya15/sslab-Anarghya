/*
================================================================================================================
Name : handsonprog3.c
Author : H Anarghya
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 10th Aug, 2023.
================================================================================================================

================================================================================================================
Sample Output:
$ ./h3 
File descriptor of created file: 3
================================================================================================================
*/

#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(){
	int fd = creat("/home/dell/file1.txt", O_RDWR);
	printf("File descriptor of created file: %d\n", fd);
	return 0;
}
