#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define MAX_TEXT 100
#define KEY 1234

struct message {
    long mtype;
    char mtext[MAX_TEXT];
};

int main() {
    int msgid = msgget(KEY, 0666 | IPC_CREAT);
    FILE *filePtr = fopen("server.log", "a");
    
    struct message msg_snd, msg_rcv;

    char tmp[MAX_TEXT];
    char *content, *count_str;
    int  count;

    printf("Server is running...\n");
    while (1) {
        msgrcv(msgid, &msg_rcv, sizeof(msg_rcv.mtext), 0, 0);
        
        strcpy(tmp, msg_rcv.mtext);
        content = strtok(tmp, "_");
        count_str = strtok(NULL, "_");
        
        if(count_str) count = atoi(count_str);
        else count = 1;

        while(count--) {
            fprintf(filePtr, "Diterima dari Client%ld: %s\n", msg_rcv.mtype, content);
        }
        fflush(filePtr);

        sprintf(msg_snd.mtext, "Balasan untuk Client%ld: Pesan diterima\n", msg_rcv.mtype);
        msg_snd.mtype = msg_rcv.mtype + 10;
        msgsnd(msgid, &msg_snd, strlen(msg_snd.mtext), 0);
    }
    
}