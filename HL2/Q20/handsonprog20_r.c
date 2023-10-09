/*
==================================================================================================
Name : handsonprog20.c
Author : H Anarghya
Description : Write two programs so that both can communicate by FIFO -Use one way communication
Date: 8th Oct, 2023.
===================================================================================================

===================================================================================================
Sample output:
$ ./read
The text from FIFO: Hello

===================================================================================================
*/
#include <stdio.h> 
#include <unistd.h>
#include <fcntl.h>

int main () { 
	int fd; 
	char buf[80];

	fd = open("myfifo", O_RDONLY); 
	read (fd, buf, sizeof (buf)); 
	printf ("The text from FIFO: %s\n", buf);
}
