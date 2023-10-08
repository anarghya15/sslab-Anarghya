/*
======================================================================================================================================================================
Name : handsonprog20.c
Author : H Anarghya
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 1st Sep, 2023.
======================================================================================================================================================================
======================================================================================================================================================================
Sample Output:
$ ./h20 7
Current priority of process: 20
Nice value = 7
New priority of the process set to: 27
======================================================================================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char* argv[]){
	int pid = getpid();
	int priority = getpriority(PRIO_PROCESS, pid);
	printf("Current priority of process: %d\n", priority+20);
	if(argc < 2){
		printf("Error, please enter a value for priority\n");
	}
	else{
		printf("Nice value = %s\n", argv[1]);
		setpriority(PRIO_PROCESS, pid, atoi(argv[1]));
		priority = getpriority(PRIO_PROCESS, pid);
		printf("New priority of the process set to: %d\n", priority+20);
	}
	//for(;;);
	return 0;
}
