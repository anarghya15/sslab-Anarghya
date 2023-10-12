/*
==================================================================================================================================================================================
Name : handsonprog32a.c
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
$ ./book_ticket 
Before entering into critical section..
Inside the critical section...
Current ticket number: 9
Press enter to unlock and exit

./book_ticket 
Before entering into critical section..
==================================================================================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>

union semun {
    int val;                    /* Value for SETVAL */
    struct semid_ds *buf;       /* Buffer for IPC_STAT, IPC_SET */
    unsigned short int *array;
};

int main() {
    struct flock fl;
    int ticketno;
    int fd = open("ticket.txt", O_RDWR);
    
    if (fd == -1) {
        printf("Error: Could not open file\n");
    } else {
        int key = ftok("../Q31/", 'b');
        int semid = semget(key, 0, 0);

        if (semid == -1) {
            perror("semget");
        }

        union semun arg;
        arg.val = 1;
        int retval = semctl(semid, 0, SETVAL, arg);

        if (retval == -1) {
            perror("semctl SETVAL");
            exit(EXIT_FAILURE);
        }

        struct sembuf sem_lock = {0, -1, SEM_UNDO};
        struct sembuf sem_unlock = {0, 1, SEM_UNDO};

        printf("Before entering into critical section...\n");
        struct sembuf sem_operation = {0, 0, SEM_UNDO};
    	int current_value = semctl(semid, 0, GETVAL, sem_operation);
    	printf("Current semaphore value: %d\n", current_value);
        retval = semop(semid, &sem_lock, 1);

        if (retval == -1) {
            perror("semop lock");
            exit(EXIT_FAILURE);
        }

        printf("Inside the critical section...\n");
        current_value = semctl(semid, 0, GETVAL, sem_operation);
    	printf("Current semaphore value: %d\n", current_value);
        read(fd, &ticketno, sizeof(ticketno));
        ticketno++;
        printf("Current ticket number: %d\n", ticketno);
        lseek(fd, 0, SEEK_SET);
        write(fd, &ticketno, sizeof(ticketno));

        printf("Press enter to unlock and exit");
        getchar();

        retval = semop(semid, &sem_unlock, 1);

        if (retval == -1) {
            perror("semop unlock");
            exit(EXIT_FAILURE);
        }

        close(fd);
        printf("Completed!\n");
    }

    return 0;
}

