/*
==============================================================================================================================
Name : handsonprog30b.c
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
$ ./h30b
Enter the text: Hi how are you
Segmentation fault (core dumped)
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
	
	int shmid = shmget(key, 1024, 0);
	
	data = shmat(shmid, 0, SHM_RDONLY);
	
	printf("Enter the text: ");
	scanf("%[^\n]", data);
	
}
	
