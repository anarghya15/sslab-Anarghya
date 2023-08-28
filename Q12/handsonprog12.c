#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char* argv[]){
	int fd = open(argv[1], O_RDWR);
	int cur_flag = fcntl(fd, F_GETFL);
	int open_mode = cur_flag & O_ACCMODE;
	if(open_mode == O_RDONLY){
		printf("The file %s is opened only for reading\n", argv[1]);
	}
	else if(open_mode  == O_WRONLY){
	       	printf("The file %s is opened only for writing\n", argv[1]);
	}
	else{
		printf("The file %s is opened for both reading and writing\n", argv[1]);
	}
	return 0;
}	
