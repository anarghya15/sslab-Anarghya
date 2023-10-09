/*
==================================================================================================
Name : handsonprog1.c
Author : H Anarghya
Description : Write two programs so that both can communicate by FIFO -Use two way communication
Date: 8th Oct, 2023.
===================================================================================================

===================================================================================================
Sample output:
$ ./p1
Enter the text: Hey
The text from FIFO: Hello
===================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main () { 
	char buf[80], buf1[80];

	int fd1, fd2;

	fd1 = open("myfifo1", O_WRONLY); 
	fd2 = open("myfifo2", O_RDONLY); 
	printf ("Enter the text: "); 	
	scanf("%[^\n]", buf); 		
	write (fd1, buf, sizeof (buf));	
	
	read (fd2, buf1, sizeof (buf1)); 
	printf ("The text from FIFO: %s\n", buf1);
	close(fd1);
	close(fd2);
	
}
