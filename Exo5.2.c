#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* genere_tableau(void* arg) {
    int* tab = malloc(5 * sizeof(int)); // Allocation dynamique
    for(int i = 0; i < 5; i++) {
        tab[i] = rand() % 100; // Aléatoire entre 0 et 99
    }
    printf("Thread : Tableau généré.\n");
    return (void*)tab; // On retourne l'adresse du tableau
}

int main() {
    pthread_t thread;
    int* tab_recu;
    srand(time(NULL));

    pthread_create(&thread, NULL, genere_tableau, NULL);
    
    // On récupère le pointeur via le deuxième argument de pthread_join
    pthread_join(thread, (void**)&tab_recu);

    printf("Main : Tableau reçu : ");
    for(int i = 0; i < 5; i++) printf("%d ", tab_recu[i]);
    printf("\n");

    free(tab_recu); // Libération de la mémoire
    return 0;
}