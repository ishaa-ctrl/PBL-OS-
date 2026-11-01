#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: ./sender <PID>\n");
        return 1;
    }

    int pid = atoi(argv[1]);

    if (kill(pid, SIGUSR1) == -1) {
        perror("kill");
        return 1;
    }

    printf("Sender: Signal sent successfully!\n");

    return 0;
}
