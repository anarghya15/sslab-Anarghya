/*
==============================================================================================================================
Name : handsonprog28.c
Author : H Anarghya
Description : Write a program to change the existing message queue permission. (use msqid_ds structure)
Date: 9th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./h28
The key is = 1627787214
The message queue id is = 0
Existing Permission: 744
New Permission: 655
$ ipcs

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61060fce 0          dell       655        0            0        
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
	
	int qid = msgget(key, 0);
	
	struct ipc_perm msg_perm; 
	
	struct msqid_ds mq;
	
	struct msginfo info;

	printf("The key is = %d\n", key);
	
	printf("The message queue id is = %d\n", qid);
	
	msgctl (qid, IPC_STAT, &mq);

	printf ("Existing Permission: %03o\n", mq.msg_perm.mode & 0777);
	
	mq.msg_perm.mode = 0655;
	
	msgctl (qid, IPC_SET, &mq);
	
	printf ("New Permission: %03o\n", mq.msg_perm.mode & 0777);
}
	
