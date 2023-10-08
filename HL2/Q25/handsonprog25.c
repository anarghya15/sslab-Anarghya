#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(){
	int key = ftok("/home/dell/greptext.txt", 'a');
	int qid = msgget(key, 0);
	struct msqid_ds *buf;

	printf("The key is = %d\n", key);
	printf("The message queue id is = %d\n", qid);
	
	int res = msgctl(qid, IPC_STAT, buf);
	printf("UID of msg queue: %u\n", buf->msg_perm.uid);
	printf("Size of the queue: %lu\n", buf->msg_cbytes);
}
