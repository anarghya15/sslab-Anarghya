/*
==================================================================================================================================================================================
Name : handsonprog17.c
Author : H Anarghya
Description : Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. 
	      Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
Date: 25th Aug, 2023.
==================================================================================================================================================================================
==================================================================================================================================================================================
Sample Output:
$ ./book_ticket 
Before entering into critical section..
Inside the critical section...
Current ticket number: 9
Press enter to unlock and exit

./book_ticket 
Before entering into critical section..
==================================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	struct flock fl;
	int ticketno;
	int fd = open("ticket.txt", O_RDWR);
	if(fd == -1){
		printf("Error: Could no open file\n");
	}
	else{
		read(fd, &ticketno, sizeof(ticketno));
		fl.l_type = F_WRLCK;
		fl.l_whence = SEEK_SET;
		fl.l_start = 0;
		fl.l_len = 0;
		fl.l_pid = getpid();
		printf("Before entering into critical section..\n");
		fcntl(fd, F_SETLKW, &fl);
		printf("Inside the critical section...\n");
		ticketno++;
		printf("Current ticket number: %d\n", ticketno);
		lseek(fd, 0, SEEK_SET);
		write(fd, &ticketno, sizeof(ticketno));
		printf("Press enter to unlock and exit");
		getchar();
		fl.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &fl);
		close(fd);
		printf("Completed!\n");
	}
	return 0;
}
