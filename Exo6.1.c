#include <stdio.h>

int main() {
    // Données du problème
    long long n_plateaux = 2;
    long long n_faces = n_plateaux * 2;
    long long n_cylindres = 1000;
    long long n_secteurs = 60;
    long long taille_secteur = 1024;

    // a) Capacité totale
    long long capacite = n_faces * n_cylindres * n_secteurs * taille_secteur;
    printf("a) Capacite totale : %lld octets\n", capacite);

    // b) Position de l'octet 300, secteur 45, cylindre 350, face 2
    // Formule : (Cyl x Faces/Cyl x Sect/Face + Face x Sect/Face + Sect) x TailleSect + Offset
    long long cyl_actuel = 350;
    long long face_actuelle = 2;
    long long sect_actuel = 45;
    long long offset_octet = 300;

    long long position = (cyl_actuel * n_faces * n_secteurs * taille_secteur) +
                         (face_actuelle * n_secteurs * taille_secteur) +
                         (sect_actuel * taille_secteur) +
                         offset_octet;
    printf("b) Position de l'octet : %lld\n", position);

    // c) Localisation de l'octet 78 000 000
    long long cible = 78000000;
    long long secteurs_par_face = n_secteurs;
    long long secteurs_par_cylindre = n_faces * n_secteurs;

    long long num_cylindre = cible / (secteurs_par_cylindre * taille_secteur);
    long long reste = cible % (secteurs_par_cylindre * taille_secteur);

    long long num_face = reste / (secteurs_par_face * taille_secteur);
    reste = reste % (secteurs_par_face * taille_secteur);

    long long num_secteur = reste / taille_secteur;
    long long pos_secteur = reste % taille_secteur;

    printf("c) Octet 78.000.000 se trouve au :\n");
    printf("   Cylindre : %lld, Face : %lld, Secteur : %lld, Position : %lld\n", 
            num_cylindre, num_face, num_secteur, pos_secteur);

    return 0;
}