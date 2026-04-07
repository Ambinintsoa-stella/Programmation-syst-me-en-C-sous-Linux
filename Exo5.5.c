//Compteur partagé et Mutex
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int compt = 0;
int limite;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* incrementer(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        if (compt >= limite) { pthread_mutex_unlock(&mutex); break; }
        compt++;
        printf("Incrémentation : %d\n", compt);
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5 + 1);
    }
    return NULL;
}

void* afficher(void* arg) {
    while(1) {
        sleep(2);
        pthread_mutex_lock(&mutex);
        printf("Lecture compteur : %d\n", compt);
        if (compt >= limite) { pthread_mutex_unlock(&mutex); break; }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char** argv) {
    if(argc < 2) return 1;
    limite = atoi(argv[1]);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, afficher, NULL);
    pthread_join(t1, NULL); pthread_join(t2, NULL);
    return 0;
}