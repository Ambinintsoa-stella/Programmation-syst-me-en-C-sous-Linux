#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("je suis le fils\n");
    } else {
        printf("je suis le père\n");
        wait(NULL);
    }
    return 0;
}