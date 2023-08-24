#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
	char str[1000] = "";
	char ch;
	int i=1;

	int fd = open("/home/dell/greptext.txt", O_RDONLY);
	while(read(fd, &ch, 1) > 0){
		if(ch == '\n'){
			printf("Line %d : %s\n", i, str);
			i++;
			strcpy(str, "");
		}
		else{
			strncat(str, &ch, 1);
		}
	}
	close(fd);
	return 0;
}
