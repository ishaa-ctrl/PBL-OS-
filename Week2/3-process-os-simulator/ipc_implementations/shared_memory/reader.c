//isha

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/isha_shared_memory"
#define SIZE 256

int main() {
    // Open existing shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);

    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Map shared memory
    char *shared_data = mmap(NULL, SIZE,
        PROT_READ, MAP_SHARED, shm_fd, 0);

    if (shared_data == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        return 1;
    }

    // Read data
    printf("Reader: Data received successfully.\n");
    printf("Reader received: %s\n", shared_data);

    munmap(shared_data, SIZE);
    close(shm_fd);

    // Remove shared memory object
    shm_unlink(SHM_NAME);

    return 0;
}
