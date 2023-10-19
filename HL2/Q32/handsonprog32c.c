#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>

#define NUM_SEMS 2

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void perror_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void sem_wait(int semid, int sem_num) {
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = -1;
    op.sem_flg = 0;
    
    if (semop(semid, &op, 1) == -1) {
        perror_exit("semop");
    }
}

void sem_signal(int semid, int sem_num) {
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = 1;
    op.sem_flg = 0;
    
    if (semop(semid, &op, 1) == -1) {
        perror_exit("semop");
    }
}

int main() {
    int semid;
    key_t key;
    union semun arg;

    if ((key = ftok(".", 'S')) == -1) {
        perror_exit("ftok");
    }

    semid = semget(key, NUM_SEMS, IPC_CREAT | 0666);
    if (semid == -1) {
        perror_exit("semget");
    }

    arg.val = 1; 
    if (semctl(semid, 0, SETVAL, arg) == -1 || semctl(semid, 1, SETVAL, arg) == -1) {
        perror_exit("semctl");
    }

    printf("Accessing Resource 1...\n");
    sem_wait(semid, 0);
    printf("Resource 1 is accessed.\n");
    sleep(3); // Simulate resource usage
    sem_signal(semid, 0);

    printf("Accessing Resource 2...\n");
    sem_wait(semid, 1);
    printf("Resource 2 is accessed.\n");
    sleep(3); // Simulate resource usage
    sem_signal(semid, 1);

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror_exit("semctl IPC_RMID");
    }

    return 0;
}

