#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	char buf[200];
	while(read(0, &buf, sizeof(buf)) > 0){
		write(1, (void*)buf, sizeof(buf));
	}

	return 0;
}
