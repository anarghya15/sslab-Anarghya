/*
==============================================================================================================================
Name : handsonprog30d.c
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
$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x00000000 10         dell       600        524288     2          dest         
0x00000000 16         dell       600        524288     2          dest         
0x62064937 17         dell       744        1024       0                       

$ ./h30d
Memory removed successfully

$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x00000000 10         dell       600        524288     2          dest         
0x00000000 16         dell       600        524288     2          dest 

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
	
	int retval = shmctl(shmid, IPC_RMID, NULL);
	if(retval == 0){
		printf("Memory removed successfully\n");
	}
	else{
		perror("shmctl");
	}
	
}
	
