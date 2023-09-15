/*
======================================================================================================================================================================
Name : handsonprog5.c
Author : H Anarghya
Description : Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 10th Aug, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ ./h5 &
[1] 3868
dell@dell-Inspiron-3576:~/sslab/Q5$ cd /proc/3868/fd
dell@dell-Inspiron-3576:/proc/3868/fd$ ls -l
total 0
lrwx------ 1 dell dell 64 Sep 10 12:26 0 -> /dev/pts/0
lrwx------ 1 dell dell 64 Sep 10 12:26 1 -> /dev/pts/0
lrwx------ 1 dell dell 64 Sep 10 12:26 2 -> /dev/pts/0
l-wx------ 1 dell dell 64 Sep 10 12:26 3 -> /home/dell/newfile.txt
l-wx------ 1 dell dell 64 Sep 10 12:26 4 -> /home/dell/newfile1.txt
l-wx------ 1 dell dell 64 Sep 10 12:26 5 -> /home/dell/newfile2.txt
l-wx------ 1 dell dell 64 Sep 10 12:26 6 -> /home/dell/newfile3.txt
l-wx------ 1 dell dell 64 Sep 10 12:26 7 -> /home/dell/newfile4.txt
======================================================================================================================================================================
*/


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
