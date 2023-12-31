/*
==============================================================================================================================
Name : handsonprog24.c
Author : H Anarghya
Description : Write a program to create a message queue and print the key and message queue id.
Date: 8th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./h24
The key is = 1627787214
The key is = 0x61060fce
The message queue id is = 0

$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61060fce 0          dell       744        0            0  
==============================================================================================================================
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(){
	int key = ftok("/home/dell/greptext.txt", 'a');
	int qid = msgget(key, IPC_CREAT|0744);

	printf("The key is = %d\n", key);
	printf("The key is = 0x%0x\n", key);
	printf("The message queue id is = %d\n", qid);
}
