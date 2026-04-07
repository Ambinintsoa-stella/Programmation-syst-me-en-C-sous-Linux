#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig) {
    FILE *f = fopen("/tmp/entier.txt", "r");
    int n;
    if (f) {
        fscanf(f, "%d", &n);
        printf("\nValeur reçue : %d\n", n);
        fclose(f);
    }
}

int main() {
    printf("Mon PID est %d. J'attends un signal...\n", getpid());
    signal(SIGUSR1, handler);
    while(1) pause(); // Attend un signal
    return 0;
}