#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

char boîte_aux_lettres;
sem_t vide, plein;

void* emetteur(void* arg) {
    for(int i=0; i<5; i++) {
        sem_wait(&vide);
        boîte_aux_lettres = 'A' + i;
        printf("Émetteur dépose : %c\n", boîte_aux_lettres);
        sem_post(&plein);
        sleep(rand()%3 + 1);
    }
    return NULL;
}

void* recepteur(void* arg) {
    for(int i=0; i<5; i++) {
        sem_wait(&plein);
        printf("Récepteur lit : %c\n", boîte_aux_lettres);
        sem_post(&vide);
        sleep(rand()%3 + 1);
    }
    return NULL;
}

int main() {
    sem_init(&vide, 0, 1);
    sem_init(&plein, 0, 0);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, emetteur, NULL);
    pthread_create(&t2, NULL, recepteur, NULL);
    pthread_join(t1, NULL); pthread_join(t2, NULL);
    return 0;
}