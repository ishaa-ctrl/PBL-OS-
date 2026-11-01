#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1",
                  &server.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&server,
                sizeof(server)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }

    char message[] = "Hello from client!";

    send(sock, message, strlen(message), 0);

    printf("Client: Message sent!\n");

    int bytes = read(sock, buffer, sizeof(buffer) - 1);

    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Client received: %s\n", buffer);
    }

    close(sock);

    return 0;
}//
