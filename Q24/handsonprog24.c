/*
======================================================================================================================================================================
Name : handsonprog24.c
Author : H Anarghya
Description : Write a program to create an orphan process
Date: 1st Sep, 2023.
======================================================================================================================================================================
======================================================================================================================================================================
Sample Output:
$ ./h24
In parent process, with PID: 6752
Child PID is: 6753
In child, process, PID: 6753
Parent PID is: 6752
dell@dell-Inspiron-3576:~/sslab/Q24$ In child, process, PID: 6753
Parent PID is: 1557

======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
	int p;
	p = fork();
	if(p==0)
    	{
    		printf("In child, process, PID: %d\n",getpid());
		printf("Parent PID is: %d\n",getppid());
		sleep(3); 
		printf("In child, process, PID: %d\n",getpid());
		printf("Parent PID is: %d\n",getppid());
    	}
	else
	{
		printf("In parent process, with PID: %d\n",getpid());
		printf("Child PID is: %d\n",p);
		exit(0);
	}
	return 0;
 }
