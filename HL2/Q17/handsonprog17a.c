/*
=================================================================================================================================================================================
Name : handsonprog17a.c
Author : H Anarghya
Description : Write a program to execute ls -l | wc.
		a. use dup
		b. use dup2
		c. use fcntl
Date: 7th Oct, 2023.
=================================================================================================================================================================================

=================================================================================================================================================================================
Sample Output:
$ ./h17a 
      3      20     115
=================================================================================================================================================================================
*/
#include <stdio.h> 
#include <unistd.h>


int main (void) { 
	int fd[2];

	pipe (fd);

	if(!fork()) {

		close (1);

		close (fd[0]);

		dup (fd[1]); 
		execlp ("ls", "ls", "-l", (char *) NULL); 
	}

	else { 
		close (0);

		close (fd[1]); 
		dup (fd[0]);

		execlp ("wc", "wc", (char *) NULL);

	}
}
