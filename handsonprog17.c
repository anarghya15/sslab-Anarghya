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
