/*
======================================================================================================================================================================
Name : handsonprog29.c
Author : H Anarghya
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 7th Sep, 2023.
======================================================================================================================================================================
======================================================================================================================================================================
Sample Output:
$ sudo ./h29
[sudo] password for dell: 
Policy used is standard round robin time sharing
Scheduling policy has been updated to real time round robin, with priority 0

 PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                                                                                                              
7633 root     -21   0    2772   1536   1536 R  95.0   0.0   2:39.08 h29  
======================================================================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<sys/types.h>
#include<sys/resource.h>
#include<sys/stat.h>

int main(){
	int policy;
	struct sched_param sp;
	sp.sched_priority = 20;
	policy = sched_getscheduler(0);
	if(policy == -1){
		perror("sched_getscheduler");
		return 0;
	}
	switch(policy){
		case SCHED_OTHER:
			printf("Policy used is standard round robin time sharing\n");
			break;
		case SCHED_FIFO:
                        printf("Policy used is real time FIFO scheduling\n");
                        break;
		case SCHED_RR:
                        printf("Policy used is real time round robin scheduling\n");
                        break;
	}

	int p = sched_setscheduler(0, SCHED_RR, &sp);

	if(p == -1){
		perror("sched_setscheduler");
		return 0;
	}
	if(sched_getscheduler(0) == SCHED_RR){
		printf("Scheduling policy has been updated to real time round robin, with priority %d\n", getpriority(PRIO_PROCESS, getpid()));
	}
	for(;;);

	return 0;
}
