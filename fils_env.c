#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *env_val = getenv("TUBE_FD");
    int fd = atoi(env_val);
    char msg[100];
    read(fd, msg, 100);
    printf("Fils (via ENV) a reçu : %s\n", msg);
    return 0;
}