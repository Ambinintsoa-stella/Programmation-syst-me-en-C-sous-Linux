#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction exécutée par le thread
void* affiche_tableau(void* arg) {
    int* tab = (int*)arg;
    printf("Contenu du tableau dans le thread : ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int mon_tab[] = {10, 20, 30, 40, 50};

    // Création du thread avec le tableau en paramètre
    if (pthread_create(&thread, NULL, affiche_tableau, (void*)mon_tab) != 0) {
        perror("Erreur de création du thread");
        return 1;
    }

    pthread_join(thread, NULL); // Attente de la fin du thread
    return 0;
}