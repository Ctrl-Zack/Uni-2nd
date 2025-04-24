#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const char *dirname = "film";

int f_count(char *genre) {
    int film, fd[2];

    pipe(fd);

    if(fork() == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        char cmd[512];
        snprintf(cmd, sizeof(cmd), "cd ./%s/%s && ls -1 | wc -l", dirname, genre);
        execlp("sh", "sh", "-c", cmd, NULL);
        exit(0);
    }

    wait(NULL);
    
    char buff[10];
    ssize_t nbytes = read(fd[0], buff, sizeof(buff) - 1);
    buff[nbytes] = '\0';
    film = atoi(buff);
    
    close(fd[0]);
    close(fd[1]);

    return film;
}

int main() {
    printf("jumlah film horror: %d\n", f_count("FilmHorror"));
    printf("jumlah film animasi: %d\n", f_count("FilmAnimasi"));
    printf("jumlah film drama: %d\n", f_count("FilmDrama"));
}