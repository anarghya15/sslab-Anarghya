/*
==============================================================================================================================
Name : handsonprog30c.c
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
$ ./h30c
Memory detached successfully

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
	const void *add;
	
	int shmid = shmget(key, 1024, 0);
	
	add = shmat(shmid, NULL, 0);
	int retval = shmdt((void*)add);
	if(retval == 0){
		printf("Memory detached successfully\n");
	}
	else{
		perror("shmdt");
	}
	
}
	
