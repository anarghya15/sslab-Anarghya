#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		perror("Please enter the source file and destination file names");
	}
	else{
		char buf[1000];
		int fd1 = open(argv[1], O_RDONLY);
		int fd2 = open(argv[2], O_WRONLY|O_CREAT, 0666);
		if(fd1 == -1 || fd2 == -1){
			printf("Could not open the source and destination file\n");
		}
		else{

			int i = read(fd1, buf, sizeof(buf));
			while(i > 0){
				write(fd2, buf, i);
				i = read(fd1, buf, sizeof(buf));
			}	
			printf("File copied successfully\n");
			close(fd1);
			close(fd2);
		}
	}
	return 0;
}
