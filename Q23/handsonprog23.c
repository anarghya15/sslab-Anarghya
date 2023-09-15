/*
======================================================================================================================================================================
Name : handsonprog23.c
Author : H Anarghya
Description : Write a program to create a Zombie state of the running program
Date: 1st Sep, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ ps aux | grep Z
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
dell        6099  0.0  0.0      0     0 pts/0    Z    16:23   0:00 [h23] <defunct>
dell        6101  0.0  0.0   9076  2432 pts/1    S+   16:24   0:00 grep --color=auto Z

======================================================================================================================================================================
*/

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
	int child_pid;
	child_pid = fork();
	if (child_pid > 0) {
		sleep (30);
	}
	else {
		exit (0);
	}
	return 0;
}
