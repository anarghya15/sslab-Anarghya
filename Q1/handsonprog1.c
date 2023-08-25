#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	//Create a hard link file
	if(link(argv[1], argv[2]) == -1){
		perror("link");
	}
	else{
		printf("Hard link file created successfully\n");
	}

	//Create a softlink file
	if(symlink(argv[1], argv[3]) == -1){
		perror("symlink");
	}
	else{
		printf("Soft link file created successfully\n");
	}

	//Create a FIFO file
	//if(mkfifo("myfifofile", S_IFIFO|S_IRWXU) == -1){
	//	perror("mkfifo");
	//}

	if(mknod(argv[4], S_IFIFO, 0) == -1){
		perror("Failed to create named pipe");
	}
	else {
		printf("FIFO file created successfully");
	}

	return 0;
}
