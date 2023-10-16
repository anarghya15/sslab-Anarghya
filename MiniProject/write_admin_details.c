#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include "structures.h"
#include "admin.h"

int main(){
    int i, fd;
    struct admin_details ad01 = {"A01", "password"};
    struct admin_details ad02 = {"A01", "password2"};
    fd = open ("admin_details.txt", O_RDWR|O_CREAT, 0666); 
	write(fd, &ad01, sizeof(ad01));
    write(fd, &ad02, sizeof(ad02));  
	close(fd);
	return 0;
}