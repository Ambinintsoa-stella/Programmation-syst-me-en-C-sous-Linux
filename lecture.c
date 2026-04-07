#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("data.bin", O_RDONLY);
    int valeur, nb;
    
    printf("Contenu du fichier :\n");
    while ((nb = read(fd, &valeur, sizeof(int))) > 0) {
        printf("%d ", valeur);
    }
    printf("\n");
    close(fd);
    return 0;
}