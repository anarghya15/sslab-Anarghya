/*
======================================================================================================================================================================
Name : handsonprog27.c
Author : H Anarghya
Description : Write a program to execute ls -Rl by the following system calls
		a. execl
		b. execlp
		c. execle
		d. execv
		e. execvp
Date: 1st Sep, 2023.
======================================================================================================================================================================
======================================================================================================================================================================
Sample Output:
$ ./execl

Executing ls -Rl using execl command:
/home/dell/Downloads:
total 225520
-rw-rw-r-- 1 dell dell     3643 Aug  4 11:52  03AugShellPrograms.tar.gz
-rw-rw-r-- 1 dell dell     1940 Sep  8 09:50  29.c
-rw-rw-r-- 1 dell dell 96126384 Jul 14 10:34  code_1.80.1-1689183569_amd64.deb
-rw-rw-r-- 1 dell dell     2829 Aug  4 11:53  employee_management.sh
-rw-rw-r-- 1 dell dell      119 Aug  4 11:53  employee_records.txt
-rw-rw-r-- 1 dell dell 94355016 Jun 26 21:41  google-chrome-stable_current_amd64.deb
-rw-rw-r-- 1 dell dell    15015 Sep 10 11:39 'Header and footer.txt'
-rw-rw-r-- 1 dell dell    58445 Jul 11 22:33 'Java - Getting Started.pdf'
-rw-rw-r-- 1 dell dell   281733 Dec 12  2021  K177B31ApplicationForm.pdf
-rw-rw-r-- 1 dell dell  2927970 Aug 10 19:49  Lect0.pptx
-rw-rw-r-- 1 dell dell  7104026 Jul 14 19:29 'Linux Fundamentals.pdf'
-rw-rw-r-- 1 dell dell  2933135 Sep  7 13:45 'MML Assignment1.pdf'
-rw-rw-r-- 1 dell dell   120872 Jul 18 13:08  MT2023083.pdf
drwxrwxr-x 2 dell dell     4096 Sep  9 10:56 'Slides Folder-20230810'
-rw-rw-r-- 1 dell dell 26963922 Aug 10 18:18 'Slides Folder-20230810.zip'

======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	char* argv[] = {"ls", "-Rl", "/home/dell/Downloads", NULL};
	printf("\nExecuting ls -Rl using execl command:\n");
	execl("/usr/bin/ls", "ls", "-R", "-l", "/home/dell/Downloads", (char*) NULL);
	return 0;
}
