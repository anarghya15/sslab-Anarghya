#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>

int main(){
	struct flock fl;
	char str[100];
	int fd = open("file.txt", O_RDWR|O_CREAT, 0666);
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_pid = getpid();
	printf("Before locking the file for writing\n");
	fcntl(fd, F_SETLKW, &fl);
	printf("Write lock acquired successfully....\n");
	printf("Enter to unlock...\n");
	getchar();
	fl.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &fl);
	printf("Finish\n");
	return 0;
}
