/*
==============================================================================================================================
Name : handsonprog27.c
Author : H Anarghya
Description : Write a program to receive messages from the message queue.
		a. with 0 as a flag
		b. with IPC_NOWAIT as a flag
Date: 8th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./h27b
Enter the message type to receive: 290
Message type: 290
 : Success
Message text: Second message to the queue      
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

	printf ("Enter the message type to receive: "); 
	scanf("%ld", &mq.mtype); 
	msgrcv (msgid, &mq, sizeof (mq.message), mq.mtype, IPC_NOWAIT); 
	printf ("Message type: %ld\n", mq.mtype); 
	perror(" ");

	printf ("Message text: %s\n", mq.message);
}
