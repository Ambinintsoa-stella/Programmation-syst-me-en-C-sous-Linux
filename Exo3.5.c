//Ouvrir plusieurs fichiers avec Emacs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char f[100];
    while (1) {
        printf("Fichier à ouvrir (q pour quitter) : ");
        scanf("%s", f);
        if (strcmp(f, "q") == 0) break;
        if (fork() == 0) {
            execl("/usr/bin/emacs", "emacs", f, NULL);
            exit(0);
        }
        wait(NULL); // On attend que l'utilisateur ferme emacs avant de demander le suivant
    }
    return 0;
}