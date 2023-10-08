#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main(){
	if(execl("/bin/sh", "sh", "/home/dell/sample.sh", (char*) NULL) == -1){
                        perror("execl");
                        exit(1);
	}
	return 0;
}
