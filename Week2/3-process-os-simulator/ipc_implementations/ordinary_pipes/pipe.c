#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char message[] = "Hello from parent";
    char buffer[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(fd[0]);

        printf("Parent: Sending message to child\n");

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);
        wait(NULL);
    }
    else {
        // Child process
        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));

        printf("Child: Received message: %s\n", buffer);

        close(fd[0]);
    }

    return 0;
}
