/*
======================================================================================================================================================================
Name : handsonprog15.c
Author : H Anarghya
Description : Write a program to display the environmental variable of the user (use environ).
Date: 25th Aug, 2023.
======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

extern char** environ;

int main(){

	int i=0;
	printf("The environment variables are:\n");
	while(environ[i] != NULL){
		printf("%s\n", environ[i++]);
	}
	return 0;
}	
