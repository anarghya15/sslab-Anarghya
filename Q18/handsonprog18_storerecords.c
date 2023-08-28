#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

int main(){

	int i, fd; 
	struct {
		int rollno;
		int marks;
	} db[3];

	for (i=0;i<3;i++){

		db[i].rollno=1+1; 
		db[i].marks=0;
	}
	fd = open ("records.txt", O_RDWR|O_CREAT, 0666); 
	write(fd, &db, sizeof(db)); 
	close(fd);
	return 0;
}
