#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>

int main(){
	int fd = open("/home/dell/newfileprog3.txt", O_RDONLY|O_EXCL);
	if(fd == -1){
		printf("open failed as named file exists\n");
	}
	return 0;
}
