#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	char buf[200];
	int i;
	while(1){
		int i = read(0, buf, sizeof(buf));
		if(i>1)
			write(1, (void*)buf, i);
		else
			break;
	}

	return 0;
}
