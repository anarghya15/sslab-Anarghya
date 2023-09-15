/*
======================================================================================================================================================================
Name : handsonprog27.c
Author : H Anarghya
Description : Write a program to execute ls -Rl by the following system calls
		a. execl
		b. execlp
		c. execle
		d. execv
		e. execvp
Date: 1st Sep, 2023.
======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	printf("\nExecuting ls -Rl using execlp command:\n");
	execlp("ls","ls", "-R", "-l", "/home/dell/Downloads", (char*) NULL);
	return 0;
}
