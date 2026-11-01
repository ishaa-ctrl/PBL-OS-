//isha

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/isha_shared_memory"
#define SIZE 256

int main() {
    // Create shared memory
    int shm_fd = shm_open(SHM_NAME,
                          O_CREAT | O_RDWR, 0666);

    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Set memory size
    if (ftruncate(shm_fd, SIZE) == -1) {
        perror("ftruncate");
        close(shm_fd);
        return 1;
    }

    // Map shared memory
    char *shared_data = mmap(NULL, SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED, shm_fd, 0);

    if (shared_data == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        return 1;
    }

    // Write data
    snprintf(shared_data, SIZE,
             "Hello from Shared Memory!");

    printf("Writer: Data written successfully.\n");
    printf("Writer: %s\n", shared_data);

    munmap(shared_data, SIZE);
    close(shm_fd);

    return 0;
}
