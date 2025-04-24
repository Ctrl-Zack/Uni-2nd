#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent process, PID = %d\n", getpid());
        sleep(30);  // Parent tidak memanggil wait()
        printf("Parent exiting...\n");
    } else if (pid == 0) {
        // Child process
        printf("Child process, PID = %d\n", getpid());
        printf("Child exiting...\n");
        exit(0);  // Child selesai
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}
