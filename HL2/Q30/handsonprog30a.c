/*
==============================================================================================================================
Name : handsonprog30a.c
Author : H Anarghya
Description : Write a program to create a shared memory.
		a. write some data to the shared memory
		b. attach with O_RDONLY and check whether you are able to overwrite.
		c. detach the shared memory
		d. remove the shared memory
Date: 9th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./h30
Enter the text: Hello

==============================================================================================================================
*/
#include <unistd.h> 

#include <stdio.h>

#include <sys/shm.h>

#include <sys/ipc.h>

#include <sys/types.h>

#include <sys/time.h> 

#include <time.h>

int main(){
	int key = ftok(".", 'b');
	char *data;
	
	int shmid = shmget(key, 1024, IPC_CREAT|0744);
	
	data = shmat(shmid, 0, 0);
	
	printf("Enter the text: ");
	scanf("%[^\n]", data);
	
}
	
