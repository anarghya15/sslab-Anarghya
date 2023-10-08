/*
======================================================================================================================================================================
Name : handsonprog9.c
Author : H Anarghya
Description : Write a program to print the following information about a given file.
	a. inode
	b. number of hard links
	c. uid
	d. gid
	e. size
	f. block size
	g. number of blocks
	h. time of last access
	i. time of last modification
	j. time of last change
Date: 18th Aug, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ ./h9 /home/dell/greptext.txt 
Details of file: /home/dell/greptext.txt
1. Inode number: 266190
2. Hard link count: 1
3. UID: 1000
4. GID: 1000
5. File size in bytes: 104
6. Block size: 4096
7. Number of blocks allocated: 8
8. Last access time: Sun Sep 10 13:19:06 2023
9. Last modification time: Fri Sep  8 23:45:29 2023
10. Last status change time: Fri Sep  8 23:45:29 2023
======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	struct stat s;

	if(argc < 2){
		perror("Error: Provide the file name as argument");
		return 1;
	}

	if(stat(argv[1], &s) == -1){
	       perror("stat");
	}

	printf("Details of file: %s\n", argv[1]);
	printf("1. Inode number: %ld\n", s.st_ino);
	printf("2. Hard link count: %lu\n", s.st_nlink);
	printf("3. UID: %u\n", s.st_uid);
	printf("4. GID: %u\n", s.st_gid);
	printf("5. File size in bytes: %ld\n", s.st_size);
	printf("6. Block size: %ld\n", s.st_blksize);
	printf("7. Number of blocks allocated: %ld\n", s.st_blocks);
	printf("8. Last access time: %s", ctime(&s.st_atime));
	printf("9. Last modification time: %s", ctime(&s.st_mtime));
	printf("10. Last status change time: %s", ctime(&s.st_ctime));

	return 0;
}	

