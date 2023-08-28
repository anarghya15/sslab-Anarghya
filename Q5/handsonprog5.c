#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(){
	int fd = creat("/home/dell/newfile.txt", O_RDWR);
	fd = creat("/home/dell/newfile1.txt", O_RDWR);
	fd = creat("/home/dell/newfile2.txt", O_RDWR);
	fd = creat("/home/dell/newfile3.txt", O_RDWR);
	fd = creat("/home/dell/newfile4.txt", O_RDWR);
	for(;;){}

	return 0;
}
