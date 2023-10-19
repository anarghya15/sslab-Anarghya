#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main() {
    int shmid, semid;
    char *shm_ptr;
    struct sembuf sem_lock = {0, -1, SEM_UNDO}; 
    struct sembuf sem_unlock = {0, 1, SEM_UNDO};

    
    int key = ftok("../Q31/", 'b');
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    if (semop(semid, &sem_lock, 1) == -1) {
        perror("semop lock");
        exit(EXIT_FAILURE);
    }

    snprintf(shm_ptr, SHM_SIZE, "Hello from the critical section!\n");
    printf("Critical section: %s", shm_ptr);

    if (semop(semid, &sem_unlock, 1) == -1) {
        perror("semop unlock");
        exit(EXIT_FAILURE);
    }

    // Detach
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}

