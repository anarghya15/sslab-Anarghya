#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(){
	int fd = creat("/home/dell/newfileprog3.txt", O_RDWR);
	printf("File descriptor of created file: %d\n", fd);
	return 0;
}
