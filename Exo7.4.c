#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf env;
int *tab;
int n;

void segfault_handler(int sig) {
    printf("\nErreur de segmentation détectée !\n");
    siglongjmp(env, 1);
}

int main() {
    printf("Taille du tableau : ");
    scanf("%d", &n);
    tab = malloc(n * sizeof(int));
    for(int i=0; i<n; i++) tab[i] = i * 10;

    int idx;
    sigsetjmp(env, 1);
    
    printf("Entrez un index à afficher : ");
    scanf("%d", &idx);

    signal(SIGSEGV, segfault_handler);
    
    // Si idx est hors limites, cela peut provoquer un crash (selon l'OS)
    // Ici on force le test pour l'exercice
    if (idx < 0 || idx >= n) {
        raise(SIGSEGV); // On simule l'erreur pour le test
    }

    printf("Valeur : %d\n", tab[idx]);
    return 0;
}