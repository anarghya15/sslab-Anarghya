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
#include<sys/stat.h>
extern char ** environ;

int main(){
	char const *env[] = {"PATH=/home/dell/Downloads", NULL};
	printf("Executing ls -Rl using execle command: \n");
	execle("/usr/bin/ls", "ls", "-R", "-l", "/home/dell/Downloads", (char*) NULL, environ);
	return 0;
}	
