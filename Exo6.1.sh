#!/bin/bash

# Configuration
FACES=4
CYLINDRES=1000
SECTEURS=60
TAILLE_SEC=1024

# a) Capacité
CAPACITE=$(( FACES * CYLINDRES * SECTEURS * TAILLE_SEC ))
echo "a) Capacité totale : $CAPACITE octets"

# b) Calcul de position
# Octet 300, Secteur 45, Cylindre 350, Face 2
C=350
F=2
S=45
O=300

POS=$(( (C * FACES * SECTEURS * TAILLE_SEC) + (F * SECTEURS * TAILLE_SEC) + (S * TAILLE_SEC) + O ))
echo "b) Position de l'octet recherché : $POS"

# c) Localisation de l'octet 78 000 000
CIBLE=78000000

# Taille d'un cylindre en octets
TAILLE_CYL=$(( FACES * SECTEURS * TAILLE_SEC ))
# Taille d'une face en octets
TAILLE_FACE=$(( SECTEURS * TAILLE_SEC ))

RES_CYL=$(( CIBLE / TAILLE_CYL ))
RESTE=$(( CIBLE % TAILLE_CYL ))

RES_FACE=$(( RESTE / TAILLE_FACE ))
RESTE=$(( RESTE % TAILLE_FACE ))

RES_SECT=$(( RESTE / TAILLE_SEC ))
RES_POS=$(( RESTE % TAILLE_SEC ))

echo "c) Pour l'octet $CIBLE :"
echo "   Cylindre : $RES_CYL"
echo "   Face     : $RES_FACE"
echo "   Secteur  : $RES_SECT"
echo "   Position : $RES_POS"