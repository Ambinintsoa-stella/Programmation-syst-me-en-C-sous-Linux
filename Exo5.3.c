#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *tab;
    int n;
    int x;
} TypeTableau;

// Thread 1 : Génération du tableau
void* generer_tableau(void* arg) {
    TypeTableau *tt = (TypeTableau*)arg;
    tt->tab = malloc(tt->n * sizeof(int));
    for(int i=0; i < tt->n; i++) {
        tt->tab[i] = rand() % 100;
    }
    printf("\n[Thread] Tableau de % d éléments généré.\n", tt->n);
    return NULL;
}

// Thread 2 : Recherche de x
void* rechercher_element(void* arg) {
    TypeTableau *tt = (TypeTableau*)arg;
    int *trouve = malloc(sizeof(int));
    *trouve = 0;
    for(int i=0; i < tt->n; i++) {
        if(tt->tab[i] == tt->x) { *trouve = 1; break; }
    }
    return (void*)trouve;
}

int main() {
    pthread_t t1, t2;
    TypeTableau data;
    srand(time(NULL));

    printf("Combien d'éléments ? ");
    scanf("%d", &data.n);

    // Lancer la génération en parallèle de la saisie de x
    pthread_create(&t1, NULL, generer_tableau, &data);

    printf("Entrez l'entier x à chercher : ");
    scanf("%d", &data.x);

    pthread_join(t1, NULL); // On attend que le tableau soit prêt

    // Lancer la recherche
    int *resultat;
    pthread_create(&t2, NULL, rechercher_element, &data);
    pthread_join(t2, (void**)&resultat);

    printf("Résultat : %s\n", (*resultat) ? "Présent" : "Absent");

    free(data.tab);
    free(resultat);
    return 0;
}