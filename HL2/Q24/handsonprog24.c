#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(){
	int key = ftok("/home/dell/greptext.txt", 'a');
	int qid = msgget(key, IPC_CREAT|0744);

	printf("The key is = %d\n", key);
	printf("The message queue id is = %d\n", qid);
}
