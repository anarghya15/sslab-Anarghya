/*
======================================================================================================================================================================
Name : handsonprog21.c
Author : H Anarghya
Description : Write a program, call fork and print the parent and child process id.
Date: 1st Sep, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ ./h21
In Parent process, pid = 5515
Child process PID = 5516
In child process, parent process PID: 5515
Child process PID: 5516

======================================================================================================================================================================
*/

#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int pid = fork();
	if(!pid){
		printf("In child process, parent process PID: %d\n", getppid());
		printf("Child process PID: %d\n", getpid());
	}
	else{
		printf("In Parent process, pid = %d\n", getpid());
		printf("Child process PID = %d\n", pid);
	}
	return 0;
}

