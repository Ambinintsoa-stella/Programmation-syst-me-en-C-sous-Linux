#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    srand(time(NULL));
    time_t debut = time(NULL);

    for (int i = 1; i <= 2; i++) {
        if (fork() == 0) {
            int d = (rand() % 10) + 1;
            sleep(d);
            printf("Fils %d a fini après %ds\n", i, d);
            exit(0);
        }
    }

    wait(NULL); wait(NULL);
    time_t fin = time(NULL);
    printf("Durée totale : %ld secondes\n", fin - debut);
    return 0;
}