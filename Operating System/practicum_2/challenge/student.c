/*
#
Buatlah program "student.c" untuk input 3 angka NRP akhir kalian dan
"verifier.c" untuk memeriksa 3 angka tersebut. Tampilkan 3 angka NRP
tersebut di terminal menggunakan "verifier.c". Gunakan message queue!

Dari program "student.c" dan "verifier.c" sebelumnya, tampilkan output
sesuai kondisi berikut. Jika angka yang diterima verifier 001 - 080,
maka verifier akan print "SNBP/IUP".
Jika angka  yang diterima 081 - 160, maka verifier akan print "SNBT",
selain itu verifier akan print "Mandiri". Output akan tercetak 5 detik
setelah NRP dicetak.
#
*/

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAXNRP 5

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 255);

    msgid = msgget(key, 0666 | IPC_CREAT);

    message.mesg_type = 1;

    printf("Input 3 NRP terakhir: ");
    fgets(message.mesg_text, MAXNRP, stdin);
    int enter = strlen(message.mesg_text) - 1;
    message.mesg_text[enter] = '\0';

    if (msgsnd(msgid, &message, sizeof(message.mesg_text), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("NRP: %s\n", message.mesg_text);

    return 0;
}
