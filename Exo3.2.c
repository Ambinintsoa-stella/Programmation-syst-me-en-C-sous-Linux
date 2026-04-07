//Copie du répertoire courant vers R
#include <unistd.h>
int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    execlp("cp", "cp", "-r", ".", argv[1], NULL);
    return 0;
}