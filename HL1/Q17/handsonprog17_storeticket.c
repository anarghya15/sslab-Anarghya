#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	int ticketno;
	int fd = open("ticket.txt", O_WRONLY);
	printf("Enter the ticket number to be stored:\n");
	scanf("%d", &ticketno);
	write(fd, &ticketno, sizeof(ticketno));
	printf("Ticket number stored succesfully\n");
	close(fd);
	return 0;
}
