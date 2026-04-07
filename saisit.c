#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    int pid_dest = atoi(argv[1]);
    int n;
    printf("Entrez un entier : ");
    scanf("%d", &n);
    FILE *f = fopen("/tmp/entier.txt", "w");
    fprintf(f, "%d", n);
    fclose(f);
    kill(pid_dest, SIGUSR1);
    return 0;
}