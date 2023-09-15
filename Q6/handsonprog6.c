/*
======================================================================================================================================================================
Name : handsonprog6.c
Author : H Anarghya
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 18th Aug, 2023.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
$./h6
Hello
Hello
Hi
Hi
Hello World
Hello World
======================================================================================================================================================================
*/
$./h6
Hello
Hello
Hi
Hi
Hello World
Hello World

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	char buf[200];
	int i;
	while(1){
		int i = read(0, buf, sizeof(buf));
		if(i>1)
			write(1, buf, i);
		else
			break;
	}

	return 0;
}
