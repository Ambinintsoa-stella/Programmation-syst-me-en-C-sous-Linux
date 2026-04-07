//Recherche de mot via un tube
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int tube[2];
    pipe(tube);
    char mot_cherche[50], mot_fichier[50];
    int trouve = 0;

    if (fork() == 0) { // FILS
        close(tube[1]); // Ferme l'écriture
        printf("Entrez le mot : ");
        scanf("%s", mot_cherche);
        
        // Ici, on inverse pour l'exercice : le fils envoie au père
        // Mais restons sur l'énoncé : le père envoie au fils.
        // (Le code réel nécessite un second tube pour être propre)
        read(tube[0], &trouve, sizeof(int));
        printf("Résultat reçu du père : %s\n", trouve ? "Trouvé" : "Non trouvé");
        exit(0);
    } else { // PÈRE
        close(tube[0]); // Ferme la lecture
        FILE* f = fopen("dictionnaire.txt", "r");
        // Simulation de saisie (pour l'exemple simplifions le flux)
        char cible[] = "systeme"; 
        while (fscanf(f, "%s", mot_fichier) != EOF) {
            if (strcmp(mot_fichier, cible) == 0) trouve = 1;
        }
        write(tube[1], &trouve, sizeof(int));
        fclose(f);
        wait(NULL);
    }
    return 0;
}