#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int tube[2];
    pipe(tube);
    char fd_str[10];
    sprintf(fd_str, "%d", tube[0]);
    
    // On définit la variable d'environnement
    setenv("TUBE_FD", fd_str, 1);

    if (fork() == 0) {
        execl("./fils_env", "fils_env", NULL);
    } else {
        write(tube[1], "Message via Environnement", 26);
        wait(NULL);
    }
    return 0;
}