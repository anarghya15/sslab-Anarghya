/*
================================================================================================================
Name : handsonprog4.c
Author : H Anarghya
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also
Date: 10th Aug, 2023.
================================================================================================================
================================================================================================================
Sample Output:
$./h4
open failed as named file exists
================================================================================================================
*/


#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>

int main(){
	int fd = open("/home/dell/file1.txt", O_RDONLY|O_CREAT|O_EXCL);
	if(fd == -1){
		printf("open failed as named file exists\n");
	}
	return 0;
}
