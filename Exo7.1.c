#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Code du fils
        while(1) {
            printf("Fils en calcul...\n");
            sleep(1);
        }
    } else { // Code du père
        char choix;
        do {
            printf("\nMenu: (s)topper, (r)edémarrer, (q)uitter : ");
            scanf(" %c", &choix);
            if (choix == 's') kill(pid, SIGSTOP);
            if (choix == 'r') kill(pid, SIGCONT);
            if (choix == 'q') {
                kill(pid, SIGTERM);
                break;
            }
        } while (1);
    }
    return 0;
}