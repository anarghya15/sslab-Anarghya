/*
======================================================================================================================================================================
Name : handsonprog8.c
Author : H Anarghya
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
Date: 18th Aug, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ ./h8
Line 1 : This is the first line.
Line 2 : This is the second line of text.
Line 3 : Hello World.
Line 4 : This is the last line.
Line 5 : dshfsadjhf
======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
	char str[1000] = "";
	char ch;
	int i=1;

	int fd = open("/home/dell/greptext.txt", O_RDONLY);
	while(read(fd, &ch, 1) > 0){
		if(ch == '\n'){
			printf("Line %d : %s\n", i, str);
			i++;
			strcpy(str, "");
		}
		else{
			strncat(str, &ch, 1);
		}
	}
	close(fd);
	return 0;
}
