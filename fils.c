#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = atoi(argv[1]); // On récupère le descripteur passé en argument
    char msg[100];
    read(fd, msg, 100);
    printf("Fils a reçu : %s\n", msg);
    return 0;
}