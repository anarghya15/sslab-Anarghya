#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Please enter the file name");
	}
	else{
		int fd = open(argv[1], O_RDWR|O_CREAT, 0666);
		write(fd, "Hello, how are you", 18);
		int loc = lseek(fd, 10, SEEK_CUR);
		printf("Location of the file pointer after lseek (in bytes): %d\n", loc);
	       	write(fd, "I'm fine, thank you.", 19);
	}

	return 0;
}	
