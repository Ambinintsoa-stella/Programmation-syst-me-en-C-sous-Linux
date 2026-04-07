#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int nb_lecteurs = 0;
pthread_mutex_t m_lecteurs = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_base = PTHREAD_MUTEX_INITIALIZER;

void* lecteur(void* arg) {
    while(1) {
        pthread_mutex_lock(&m_lecteurs);
        nb_lecteurs++;
        if(nb_lecteurs == 1) pthread_mutex_lock(&m_base); // Le 1er bloque les rédacteurs
        pthread_mutex_unlock(&m_lecteurs);

        printf("Lecteur lit la base (%d lecteurs présents)\n", nb_lecteurs);
        sleep(rand()%3 + 1);

        pthread_mutex_lock(&m_lecteurs);
        nb_lecteurs--;
        if(nb_lecteurs == 0) pthread_mutex_unlock(&m_base); // Le dernier libère
        pthread_mutex_unlock(&m_lecteurs);
        sleep(1);
    }
}

void* redacteur(void* arg) {
    while(1) {
        pthread_mutex_lock(&m_base); // Un seul rédacteur à la fois
        printf("!!! RÉDACTEUR modifie la base !!!\n");
        sleep(rand()%5 + 2);
        pthread_mutex_unlock(&m_base);
        sleep(rand()%10 + 1);
    }
}

int main() {
    pthread_t l[5], r[2];
    for(int i=0; i<5; i++) pthread_create(&l[i], NULL, lecteur, NULL);
    for(int i=0; i<2; i++) pthread_create(&r[i], NULL, redacteur, NULL);
    pthread_join(l[0], NULL);
    return 0;
}