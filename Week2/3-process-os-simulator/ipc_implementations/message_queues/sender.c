// haneena
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok(".", 65);

    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    struct message msg;
    msg.msg_type = 1;

    printf("Enter message: ");
    fgets(msg.msg_text, sizeof(msg.msg_text), stdin);

    msg.msg_text[strcspn(msg.msg_text, "\n")] = '\0';

    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("Message sent successfully!\n");

    return 0;
}
