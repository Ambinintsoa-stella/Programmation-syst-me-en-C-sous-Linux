#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int tube[2];
    pipe(tube);

    if (fork() == 0) {
        // Côté FILS : on veut lire ce que le père envoie
        close(tube[1]); 
        dup2(tube[0], STDIN_FILENO); // On lie l'entrée standard au tube
        char mot[50];
        scanf("%s", mot); // Lit depuis le tube comme si c'était le clavier
        printf("Le fils a lu via stdin : %s\n", mot);
        close(tube[0]);
    } else {
        // Côté PÈRE : on veut écrire vers le fils
        close(tube[0]);
        dup2(tube[1], STDOUT_FILENO); // On lie la sortie standard au tube
        printf("Message_Secret"); // Écrit dans le tube au lieu de l'écran
        fflush(stdout); 
        close(tube[1]);
        wait(NULL);
    }
    return 0;
}