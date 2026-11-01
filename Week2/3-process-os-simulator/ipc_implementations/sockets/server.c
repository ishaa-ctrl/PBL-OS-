//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("Server: Waiting for client...\n");

    socklen_t addrlen = sizeof(address);
    client_fd = accept(server_fd,
        (struct sockaddr *)&address, &addrlen);

    if (client_fd < 0) {
        perror("accept");
        close(server_fd);
        return 1;
    }

    read(client_fd, buffer, sizeof(buffer));

    printf("Server received: %s\n", buffer);

    char reply[] = "Hello from server!";
    send(client_fd, reply, strlen(reply), 0);

    printf("Server: Response sent!\n");

    close(client_fd);
    close(server_fd);

    return 0;
}
