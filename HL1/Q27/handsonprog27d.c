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
	char* argv[] = {"ls", "-Rl", "/home/dell/Downloads", NULL};
	printf("\nExecuting ls -Rl using execv command:\n");
	execv("/usr/bin/ls", argv);
	return 0;
}
