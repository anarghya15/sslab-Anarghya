#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

extern char** environ;

int main(){

	int i=0;
	printf("The environment variables are:\n");
	while(environ[i] != NULL){
		printf("%s\n", environ[i++]);
	}
	return 0;
}	
