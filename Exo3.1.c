//Addition d'arguments
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    // atoi convertit une chaîne (ASCII) en entier (integer)
    printf("%d\n", atoi(argv[1]) + atoi(argv[2]));
    return 0;
}