//Ouvrir un fichier saisi au clavier avec Emacs
#include <stdio.h>
#include <unistd.h>

int main() {
    char nom[100];
    printf("Nom du fichier : ");
    scanf("%s", nom);
    execl("/usr/bin/emacs", "emacs", nom, NULL);
    return 0;
}