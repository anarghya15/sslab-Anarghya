/*
======================================================================================================================================================================
Name : handsonprog15.c
Author : H Anarghya
Description : Write a simple program to send some data from parent to the child process.
Date: 7th Oct, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$$ ./h15 
Enter message to child:Hello child
Message from parent: Hello child
======================================================================================================================================================================
*/
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
#define MAX 10 
  
int main() 
{ 
  
  	int fd[2], i=0; 
  	pipe(fd);
  	char arr[100]; 
  	pid_t pid = fork(); 
  	if(pid > 0) {
  		// no need to use the write end of pipe here so close it 
      	  	close(fd[0]);  
		printf("Enter message to child:");
		scanf("%[^\n]", arr);
		write(fd[1], arr, sizeof(arr));
 	}  
	else if( pid == 0 ) { 
		close(fd[1]);
		// n stores the total bytes read successfully 
      		read(fd[0], arr, sizeof(arr)); 
      		printf("Message from parent: %s\n", arr);
	}  

	else { 
		perror("Error\n"); //fork() 
	} 
}
