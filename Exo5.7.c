#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

double u = 1.0;
int compt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* T1(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        u = pow(u - 1, 2) / 4.0; // f1(x) = (x-1)^2 / 4
        compt++;
        printf("[T1] u = %f (iter %d)\n", u, compt);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 5 + 1);
    }
}

void* T2(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        u = pow(u - 2, 2) / 6.0; // f2(x) = (x-2)^2 / 6
        compt++;
        printf("[T2] u = %f (iter %d)\n", u, compt);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 5 + 1);
    }
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, T1, NULL);
    pthread_create(&t2, NULL, T2, NULL);
    pthread_join(t1, NULL);
    return 0;
}