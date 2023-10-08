/*
==================================================================================================
Name : handsonprog1.c
Author : H Anarghya
Description : 1. Create the following types of a files using (i) shell command (ii) system call
		a. soft link (symlink system call)
		b. hard link (link system call)
		c. FIFO (mkfifo Library Function or mknod system call)
Date: 10th Aug, 2023.
===================================================================================================

===================================================================================================
Sample output:
$./h1 /home/dell/file1.txt /home/dell/hardlink.txt /home/dell/softlink.txt myfifo 
Hard link file created successfully
Soft link file created successfully
FIFO file created successfully
===================================================================================================
*/

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		perror("Please enter the source file and destination file names");
	}
	else{
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
			printf("FIFO file created successfully\n");
		}
	}
	return 0;
}
