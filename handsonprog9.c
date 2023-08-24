#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	struct stat s;

	if(argc < 2){
		perror("Provide the file name as argument");
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

