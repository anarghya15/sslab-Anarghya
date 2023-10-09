/*
==============================================================================================================================
Name : handsonprog29.c
Author : H Anarghya
Description : Write a program to remove the message queue.
Date: 9th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./h29
Message queue with id 0 is removed
$ ipcs

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
 
==============================================================================================================================
*/
#include <unistd.h> 

#include <stdio.h>

#include <sys/msg.h>

#include <sys/ipc.h>

#include <sys/types.h>

#include <sys/time.h> 

#include <time.h>

int main(){
	int key = ftok("/home/dell/greptext.txt", 'a');
	
	int msqid = msgget(key, 0);
	
	int rtrn = msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
	
	if(rtrn == 0){
		printf("Message queue with id %d is removed\n", msqid);
	}
	
}
	
