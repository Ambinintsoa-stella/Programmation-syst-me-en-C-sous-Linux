// Combinaison sans boucle ni récursion de fonction
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    // Cas de base
    if (k == 0 || k == n) { printf("1\n"); return 1; }

    // On crée deux fils pour calculer C(n-1, k-1) et C(n-1, k)
    int p1[2], p2[2];
    pipe(p1); // Utilisation de pipes pour lire le résultat (plus propre que /tmp)
    
    if (fork() == 0) {
        dup2(p1[1], 1); // Redirige stdout vers le pipe
        char sn[10], sk[10];
        sprintf(sn, "%d", n-1); sprintf(sk, "%d", k-1);
        execl(argv[0], argv[0], sn, sk, NULL);
    }
    
    // ... Idem pour le deuxième fils, puis le père additionne les sorties.
    // (Note : Dans un cadre scolaire strict, on utiliserait des fichiers dans /tmp)

    else
    {
        if (fork() == 0) {
           dup2(p2[1], 1); // Redirige stdout vers le pipe
            char snn[10], skk[10];
            sprintf(snn, "%d", n-1); sprintf(skk, "%d", k);
            execl(argv[0], argv[0], snn, skk, NULL);
        }
    }
    
    return 0;
}