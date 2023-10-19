/*
==================================================================================================================================================================================
Name : handsonprog32d.c
Author : H Anarghya
Description : Write a program to implement semaphore to protect any critical section.
		a. rewrite the ticket number creation program using semaphore
		b. protect shared memory from concurrent write access
		c. protect multiple pseudo resources ( may be two) using counting semaphore
		d. remove the created semaphore
Date: 10th Oct, 2023.
==================================================================================================================================================================================
==================================================================================================================================================================================
Sample Output:
$ ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x62064940 1          dell       666        1         
0x0000d431 2          dell       666        1         

$ ./h32d
Semaphore set removed successfully.
$ ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x0000d431 2          dell       666        1
==================================================================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main() {
    key_t key;
    int semid;

    if ((key = ftok("../Q31", 'b')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

   semid = semget(key, 0, 0);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore set removed successfully.\n");

    return 0;
}

