#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 12345  // Shared memory key
#define SEM_KEY 54321  // Semaphore key
#define SHM_SIZE 1024  // Size of shared memory

int main() {
    int shmid, semid;
    char *shm_ptr;
    struct sembuf sem_lock = {0, -1, SEM_UNDO}; // Semaphore lock operation
    struct sembuf sem_unlock = {0, 1, SEM_UNDO}; // Semaphore unlock operation

    // Create a semaphore
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore value to 1 (unlocked)
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Create or access the shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment to the process's address space
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Enter the critical section
    if (semop(semid, &sem_lock, 1) == -1) {
        perror("semop lock");
        exit(EXIT_FAILURE);
    }

    // Access and modify the shared memory (simulated critical section)
    snprintf(shm_ptr, SHM_SIZE, "Hello from the critical section!\n");
    printf("Critical section: %s", shm_ptr);

    // Leave the critical section
    if (semop(semid, &sem_unlock, 1) == -1) {
        perror("semop unlock");
        exit(EXIT_FAILURE);
    }

    // Detach the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}

