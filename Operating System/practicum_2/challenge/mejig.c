/*
#
Buatlah program "mejig.c" yang menjalankan dua proses:
- Proses pertama membuat direktori 'myfolder'.
- Proses kedua menunggu sampai direktori dibuat, kemudian membuat file 'myfile.txt' di dalam 'myfolder'.
Gunakan fork, exec, dan wait dalam implementasinya.
#
#
Dapatkan PID dari process "mejig.c" yang sudah dijalankan melalui terminal
ps aux | grep mejig
#
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    __pid_t pid[2];

    pid[0] = fork();
    if(pid[0] == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "mkdir -p myfolder");
        execlp("sh", "sh", "-c", cmd, NULL);
    }
    waitpid(pid[0], NULL, 0);
    
    pid[1] = fork();
    if(pid[1] == 0) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd myfolder && touch myfile.txt");
        execlp("sh", "sh", "-c", cmd, NULL);
    }
    waitpid(pid[1], NULL, 0);

    sleep(5);
}