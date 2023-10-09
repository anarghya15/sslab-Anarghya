/*
==================================================================================================
Name : handsonprog1.c
Author : H Anarghya
Description : Write two programs so that both can communicate by FIFO -Use one way communication
Date: 8th Oct, 2023.
===================================================================================================

===================================================================================================
Sample output:
$ ./write
Enter the text: Hello

===================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main () { 
	char buf[80];

	int fd;

	fd = open("myfifo", O_WRONLY); 
	
	printf ("Enter the text: "); 
	
	scanf("%[^\n]", buf); 
	
	write (fd, buf, sizeof (buf));
}
