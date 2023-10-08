/*
======================================================================================================================================================================
Name : handsonprog9.c
Author : H Anarghya
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 7th Oct, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$ ./h16
Enter message to child:Hello child
Message from parent: Hello child
Enter message to parent:Hello parent
Message from child: Hello parent

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
  	int fd1[2], fd2[2], i=0; 
  	char arr1[100], arr2[100];
  	pipe(fd1);
  	pipe(fd2);  
  	pid_t pid = fork(); 
  	if(pid > 0) {
  		close(fd1[1]); 
      	  	close(fd2[0]); 
		printf("Enter message to child:");
		scanf("%[^\n]", arr1);
		write(fd2[1], arr1, sizeof(arr1));
		read(fd1[0], arr2, sizeof(arr2)); 
      		printf("Message from child: %s\n", arr2);
 	}  
	else if( pid == 0 ) { 
		close(fd2[1]); 
      	  	close(fd1[0]); 
      	  	read(fd2[0], arr1, sizeof(arr1)); 
      		printf("Message from parent: %s\n", arr1);
		printf("Enter message to parent:");
		scanf("%[^\n]", arr2);
		write(fd1[1], arr2, sizeof(arr2));
		
	}  

	else { 
		perror("Error\n"); //fork() 
	} 
	wait(0);
}
