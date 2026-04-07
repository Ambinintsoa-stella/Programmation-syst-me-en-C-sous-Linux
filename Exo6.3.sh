#!/bin/bash
# PARTIE A : Écriture (on simule le binaire via un format hex)
tab=(10 20 30 40)
# Création du fichier et changement de droits
touch data.bin
chmod 664 data.bin
printf "%08x" "${tab[@]}" | xxd -r -p > data.bin

# PARTIE B : Lecture
echo "Lecture binaire (via od) :"
od -An -t dI data.bin