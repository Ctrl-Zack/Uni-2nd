#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define CLIENT_ID 1
#define MAX_TEXT 100
#define KEY 1234

struct message {
    long mtype;
    char mtext[MAX_TEXT];
};


int main() {
    int msgid = msgget(KEY, 0666 | IPC_CREAT);
    char buffer[MAX_TEXT];

    struct message msg_snd, msg_rcv;

    while (1) {
        printf("Client1> \n");
        fgets(buffer, MAX_TEXT, stdin);
        
        msg_snd.mtype = CLIENT_ID;
        strcpy(msg_snd.mtext, buffer);

        msgsnd(msgid, &msg_snd, strlen(msg_snd.mtext) + 1, 0);
        msgrcv(msgid, &msg_rcv, MAX_TEXT, CLIENT_ID + 10, 0);
    
        printf("Client2: %s", msg_rcv.mtext);
    }
    
}