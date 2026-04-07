#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem1, sem2;

void* thread1(void* arg) {
    for(int i=0; i<10; i++) {
        sleep(2); // Traitement
        printf("T1 prêt au rendez-vous %d\n", i);
        sem_post(&sem1); // Signale sa présence
        sem_wait(&sem2); // Attend T2
        printf("T1 repart %d\n", i);
    }
    return NULL;
}

void* thread2(void* arg) {
    for(int i=0; i<10; i++) {
        sleep(rand()%6 + 4); // Traitement long
        printf("T2 prêt au rendez-vous %d\n", i);
        sem_post(&sem2); // Signale sa présence
        sem_wait(&sem1); // Attend T1
        printf("T2 repart %d\n", i);
    }
    return NULL;
}

int main() {
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL); pthread_join(t2, NULL);
    sem_destroy(&sem1); sem_destroy(&sem2);
    return 0;
}