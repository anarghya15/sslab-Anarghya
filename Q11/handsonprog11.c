#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(){
	int fd = open("prog11.txt", O_RDWR|O_APPEND);
	int fd2, fd3, fd4;
	if(fd == -1)
	{
		perror("open");
	}
	else{
		printf("Using dup\n");
		fd2 = dup(fd);
		printf("fd1 = %d\n", fd);
		printf("fd2 = %d\n", fd2);
		write(fd, "This is written by the original file descriptor\n", 48);
		write(fd2, "This is written by the duplicate file descriptor\n", 49);
		printf("Duplication successful...\n");
		printf("Using dup2\n");
		fd3 = dup2(fd, 27);
		printf("fd1 = %d\n", fd);
		printf("fd2 = %d\n", fd3);
		write(fd, "Using dup2\nThis is written by the original file descriptor\n", 59);
		write(fd2, "This is written by the duplicate file descriptor\n", 49);
		printf("Duplication successful...\n");
		printf("Using fcntl\n");
		fd4 = fcntl(fd, F_DUPFD, 27);
		printf("fd1 = %d\n", fd);
		printf("fd2 = %d\n", fd4);
		write(fd, "Using fcntl\nThis is written by the original file descriptor\n", 60);
		write(fd2, "This is written by the duplicate file descriptor\n", 49);
		printf("Duplication successful...\n");
		close(fd);
		close(fd2);
		close(fd3);
		close(fd4);
	}
	return 0;
}
