#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    printf("\nReceiver: Signal received successfully!\n");
}

int main() {
    signal(SIGUSR1, handle_signal);

    printf("Receiver PID: %d\n", getpid());
    printf("Receiver: Waiting for signal...\n");

    pause();

    return 0;
}
