#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	int fd[2];
	char msg[] = "Message written to write end of the pipe";
	char buf[100];

	pipe(fd);

	int i = write(fd[1], msg, sizeof(msg));

	read(fd[0], buf, i);

	printf("Message read from pipe: %s\n", buf);

	return 0;
}
	
