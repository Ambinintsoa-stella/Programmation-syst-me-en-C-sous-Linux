#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int *t1, *t2;
    int n1, n2;
} Comparaison;

// Thread d'annulation
void* check_cancel(void* arg) {
    char c;
    while(1) {
        c = getchar();
        if(c == 'A' || c == 'a') {
            printf("\n[ANNULATION] Le programme s'arrête.\n");
            exit(0);
        }
    }
}

void* verifier_inclusion(void* arg) {
    Comparaison *c = (Comparaison*)arg;
    for(int i=0; i < c->n1; i++) {
        int trouve = 0;
        for(int j=0; j < c->n2; j++) {
            if(c->t1[i] == c->t2[j]) { trouve = 1; break; }
        }
        if(!trouve) return (void*)0; // Non inclus
    }
    return (void*)1; // Inclus
}

int main() {
    pthread_t t_inc, t_cancel;
    Comparaison data = {NULL, NULL, 5, 10}; // Exemple de tailles
    
    // Initialisation simplifiée pour l'exemple
    data.t1 = malloc(data.n1 * sizeof(int));
    data.t2 = malloc(data.n2 * sizeof(int));
    for(int i=0; i<10; i++) data.t2[i] = i; 
    for(int i=0; i<5; i++) data.t1[i] = i;

    pthread_create(&t_cancel, NULL, check_cancel, NULL);
    
    printf("Calcul de l'inclusion en cours... (Appuyez sur 'A' pour annuler)\n");
    sleep(2); // Pour laisser le temps d'annuler

    int *res;
    pthread_create(&t_inc, NULL, verifier_inclusion, &data);
    pthread_join(t_inc, (void**)&res);

    printf("Résultat : %s\n", (long)res ? "T1 est dans T2" : "T1 n'est pas dans T2");

    return 0;
}