/*
======================================================================================================================================================================
Name : handsonprog10.c
Author : H Anarghya
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
a. check the return value of lseek
b. open the file with od and check the empty spaces in between the data.
Date: 18th Aug, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ ./h10 prog10.txt 
Location of the file pointer after lseek (in bytes): 28
$ od -c prog10.txt 
0000000   H   e   l   l   o   ,       h   o   w       a   r   e       y
0000020   o   u  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0   I   '   m    
0000040   f   i   n   e   ,       t   h   a   n   k       y   o   u
0000057
======================================================================================================================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Error: Please enter the file name as argument");
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
