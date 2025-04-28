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
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 255);

    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgrcv(msgid, &message, sizeof(message.mesg_text), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("NRP: %s\n", message.mesg_text);
    int nrp = atoi(message.mesg_text);
    sleep(5);
    if(nrp >= 1 && nrp <= 80) printf("SNBP/IUP\n");
    else if(nrp >= 81 && nrp <= 160) printf("SNBT\n");
    else printf("Mandiri\n");

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
