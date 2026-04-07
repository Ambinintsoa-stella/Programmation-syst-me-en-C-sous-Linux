#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

void message_mort(int sig) {
    printf("\n[Fils %d] Je meurs !\n", getpid());
    exit(0);
}

int main() {
    pid_t fils[5];
    for(int i=0; i<5; i++) {
        fils[i] = fork();
        if (fils[i] == 0) {
            signal(SIGTERM, message_mort);
            while(1) pause();
        }
    }

    int num, cmd;
    while(1) {
        printf("\nFils (0-4) et Action (1:Stop, 2:Cont, 3:Term) : ");
        scanf("%d %d", &num, &cmd);
        if (num < 0 || num > 4) continue;
        if (cmd == 1) kill(fils[num], SIGSTOP);
        if (cmd == 2) kill(fils[num], SIGCONT);
        if (cmd == 3) kill(fils[num], SIGTERM);
    }
    return 0;
}