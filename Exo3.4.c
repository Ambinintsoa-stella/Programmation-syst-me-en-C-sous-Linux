//Copie multiple (Boucle)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char dest[100];
    while (1) {
        printf("Destination (q pour quitter) : ");
        scanf("%s", dest);
        if (strcmp(dest, "q") == 0) break;
        if (fork() == 0) {
            execlp("cp", "cp", "-r", ".", dest, NULL);
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}