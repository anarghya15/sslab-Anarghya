/*
==============================================================================================================================
Name : handsonprog26.c
Author : H Anarghya
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 8th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./h26 
Enter the message type: 102
Enter the message text: First message to message queue

$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61060fce 0          dell       744        45           3         
==============================================================================================================================
*/
#include <sys/msg.h> 

#include <sys/ipc.h>

#include <sys/types.h>

#include <string.h>

#include <stdio.h>

int main () {

	int msgid, size;

	key_t key;

	struct msg {

		long int mtype; 
		char message [80];

	}mq;

	key = ftok("/home/dell/greptext.txt", 'a');
	
	msgid = msgget(key, 0);
	
	printf ("Enter the message type: "); 
	
	scanf("%ld", &mq.mtype);
	
	getchar();
	
	printf ("Enter the message text: "); 
	
	scanf("%[^\n]", mq.message); 
	
	size = strlen (mq.message);

	msgsnd (msgid, &mq, size+1, 0);
}
