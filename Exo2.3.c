#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 5; i++) {
        if (fork() == 0) {
            printf("Processus fils créé\n");
            exit(0); // CRITIQUE : on quitte pour que le fils ne boucle pas
        }
    }
    for (int i = 0; i < 5; i++) wait(NULL);
    return 0;
}