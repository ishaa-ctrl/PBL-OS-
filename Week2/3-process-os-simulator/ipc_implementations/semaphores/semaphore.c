//isha

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

int main() {
    // Create shared memory for semaphore
    sem_t *sem = mmap(NULL, sizeof(sem_t),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (sem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Initialize semaphore with value 0
    if (sem_init(sem, 1, 0) == -1) {
        perror("sem_init");
        munmap(sem, sizeof(sem_t));
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child: Waiting for semaphore...\n");

        if (sem_wait(sem) == -1) {
            perror("sem_wait");
            _exit(1);
        }

        printf("Child: Semaphore received!\n");
        printf("Child: Critical operation completed.\n");

        _exit(0);
    }
    else {
        // Parent process
        sleep(2);

        printf("Parent: Sending semaphore signal.\n");

        if (sem_post(sem) == -1) {
            perror("sem_post");
        }

        wait(NULL);

        printf("Parent: Child process completed.\n");

        sem_destroy(sem);
        munmap(sem, sizeof(sem_t));
    }

    return 0;
}
