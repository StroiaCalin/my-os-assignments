#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define RESP_PIPE_NAME "RESP_PIPE_93193"
#define REQ_PIPE_NAME "REQ_PIPE_93193"

int main() {
    int pipe1, pipe2;
    char aux[250];
    if (mkfifo(RESP_PIPE_NAME, 0644) != 0) {
        printf("ERROR\nCannot create the response pipe\n");
        exit(1);
    }
    pipe2 = open(REQ_PIPE_NAME, O_RDONLY);
    if (pipe2 == -1) {
        printf("ERROR\ncannot open the request pipe\n");
        exit(1);
    }
    pipe1 = open(RESP_PIPE_NAME, O_WRONLY);
    if (pipe1 == -1) {
        printf("ERROR\ncannot open the response pipe\n");
        exit(1);
    }
    strcpy(aux, "HELLO#");
    write(pipe1,aux, strlen(aux));
    return 0;
}

