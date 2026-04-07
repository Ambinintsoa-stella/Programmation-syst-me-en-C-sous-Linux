#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

void lister_gros_fichiers(char *chemin) {
    DIR *dir = opendir(chemin);
    if (!dir) return;

    struct dirent *ent;
    struct stat st;
    char chemin_complet[1024];

    while ((ent = readdir(dir)) != NULL) {
        sprintf(chemin_complet, "%s/%s", chemin, ent->d_name);
        if (stat(chemin_complet, &st) == 0) {
            if (S_ISREG(st.st_mode) && st.st_size > 1000000) {
                printf("Fichier: %s | Taille: %ld octets | UID: %d\n", 
                        ent->d_name, st.st_size, st.st_uid);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) lister_gros_fichiers(argv[i]);
    return 0;
}