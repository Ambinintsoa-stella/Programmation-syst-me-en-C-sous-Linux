#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 100
double tableau[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_calcul(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        for (int i = 1; i < N - 1; i++) {
            tableau[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0;
        }
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

void* thread_affichage(void* arg) {
    while(1) {
        sleep(4);
        pthread_mutex_lock(&mutex);
        printf("\n[Affichage] Valeurs centrales : %.2f, %.2f, %.2f\n", 
                tableau[1], tableau[50], tableau[98]);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    for(int i=0; i<N; i++) tableau[i] = (i == 0 || i == 99) ? 0 : rand() % 101;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_calcul, NULL);
    pthread_create(&t2, NULL, thread_affichage, NULL);
    
    pthread_join(t1, NULL); // En pratique, boucle infinie ici
    return 0;
}