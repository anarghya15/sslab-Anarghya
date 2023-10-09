/*
==============================================================================================================================
Name : handsonprog25.c
Author : H Anarghya
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
		a. access permission
		b. uid, gid
		c. time of last message sent and received
		d. time of last change in the message queue
		d. size of the queue
		f. number of messages in the queue
		g. maximum number of bytes allowed
		h. pid of the msgsnd and msgrcv
Date: 8th Oct, 2023.
==============================================================================================================================

==============================================================================================================================
Sample output:
$ ./h25 
The key is = 1627787214
The message queue id is = 0
Effective UID of owner: 0
Effective GID of owner: 0
Effective UID of creator: 0
Effective GID of creator: 0
Permission: 744
Current number of messages in queue: 0
PID of last msgsnd: 0
PID of las msgrce: 0
Time of last msgsnd: Thu Jan  1 05:30:00 1970
Time of last msgreceive: Thu Jan  1 05:30:00 1970
Time of last change: Sun Oct  8 20:40:03 2023
Maximum number of bytes allowed in queue: 16384
Current number of bytes in queue: 0
Size (KB) of buffer pool used to hold message data (uwk): 10
Maximum number of entries in message map: 8
Maximum number of bytes that can be written in single message: 0
Maximum number of bytes that can be written to queue: used to initialize msg_qbytes during queue creation (msgget): 0
Maximum number of message queues: 0
Message segment size (uwk): 0
Maximum nuber of messages on all queues in system (uwk): 0
Maximum number of segments (uwk): 0
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

	printf ("Effective UID of owner: %d\n", msg_perm.uid); 
	
	printf ("Effective GID of owner: %d\n", msg_perm.gid);

	printf ("Effective UID of creator: %d\n", msg_perm.cuid);

	printf ("Effective GID of creator: %d\n", msg_perm.cgid); 
	
	printf ("Permission: %03o\n", mq.msg_perm.mode & 0777);

	printf ("Current number of messages in queue: %lu\n", mq.msg_qnum); 
	
	printf ("PID of last msgsnd: %d\n", mq.msg_lspid);

	printf ("PID of las msgrce: %d\n", mq.msg_lrpid);

	printf ("Time of last msgsnd: %s", ctime (&mq.msg_stime));

	printf ("Time of last msgreceive: %s", ctime (&mq.msg_rtime)); 
	
	printf ("Time of last change: %s", ctime (&mq.msg_ctime));

	printf ("Maximum number of bytes allowed in queue: %lu\n", mq.msg_qbytes); 
	
	printf ("Current number of bytes in queue: %lu\n", mq.msg_cbytes);

	printf ("Size (KB) of buffer pool used to hold message data (uwk): %d\n", info.msgpool);

	printf ("Maximum number of entries in message map: %d\n", info.msgmap); 
	
	printf ("Maximum number of bytes that can be written in single message: %d\n", info.msgmax);

	printf ("Maximum number of bytes that can be written to queue: used to initialize msg_qbytes during queue creation (msgget): %d\n", info.msgmnb);

	printf ("Maximum number of message queues: %d\n", info.msgmni);
	
	printf ("Message segment size (uwk): %d\n", info.msgssz);

	printf ("Maximum nuber of messages on all queues in system (uwk): %d\n", info.msgtql);

	printf ("Maximum number of segments (uwk): %d\n", info.msgseg);
	
}
