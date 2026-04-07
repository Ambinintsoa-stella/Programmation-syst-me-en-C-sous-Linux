#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE 10
char tampon[TAILLE];
int index_tampon = 0;

sem_t places_libres, objets_prets;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* producteur(void* arg) {
    while(1) {
        sem_wait(&places_libres);
        pthread_mutex_lock(&mutex);
        tampon[index_tampon++] = 'P';
        printf("[Prod] Objet ajouté. Stock : %d\n", index_tampon);
        pthread_mutex_unlock(&mutex);
        sem_post(&objets_prets);
        sleep(rand()%3 + 1);
    }
}

void* consommateur(void* arg) {
    while(1) {
        sem_wait(&objets_prets);
        pthread_mutex_lock(&mutex);
        index_tampon--;
        printf("[Cons] Objet retiré. Stock : %d\n", index_tampon);
        pthread_mutex_unlock(&mutex);
        sem_post(&places_libres);
        sleep(rand()%3 + 1);
    }
}

int main() {
    sem_init(&places_libres, 0, TAILLE);
    sem_init(&objets_prets, 0, 0);
    pthread_t p[3], c[2]; // 3 producteurs, 2 consommateurs
    for(int i=0; i<3; i++) pthread_create(&p[i], NULL, producteur, NULL);
    for(int i=0; i<2; i++) pthread_create(&c[i], NULL, consommateur, NULL);
    pthread_join(p[0], NULL);
    return 0;
}