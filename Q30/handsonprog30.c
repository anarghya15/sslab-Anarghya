/*
======================================================================================================================================================================
Name : handsonprog30.c
Author : H Anarghya
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 7th Sep, 2023.
======================================================================================================================================================================
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
int main ()
{
	int pid, i;
	pid = fork ();
	if (pid == -1)
		return -1;
	else if (pid != 0)
		exit (0);
	
	if (setsid () == -1)
		return -1;

	if (chdir ("/") == -1)
		return -1;

	umask(0);

	for (i = 0; i < 3; i++){
		close (i);
	}

	open ("/dev/null", O_RDWR);
	dup (0);
	dup (0);

	/*struct tm t;
    	t.tm_hour = 14;
    	t.tm_min = 30;
    	t.tm_sec = 0;*/

    	while (1) {
		/*if(execl("/bin/sh", "sh", "/home/dell/sample.sh", (char*) NULL) == -1){
			perror("execl");
			exit(1);
		}*/
        	sleep(60); 
	}
	
	return 0;
}
