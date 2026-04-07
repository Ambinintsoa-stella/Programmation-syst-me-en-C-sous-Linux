#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int n, fd;
    printf("Combien d'entiers ? ");
    scanf("%d", &n);
    int tab[n];
    for(int i=0; i<n; i++) scanf("%d", &tab[i]);

    // Permissions: rw-rw-r-- (664 octal)
    fd = open("data.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    write(fd, tab, sizeof(tab));
    close(fd);
    return 0;
}