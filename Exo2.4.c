#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 1; i <= 5; i++) {
        if (fork() == 0) {
            printf("je suis le fils %d\n", i);
            exit(0);
        }
    }
    for (int i = 0; i < 5; i++) wait(NULL);
    return 0;
}