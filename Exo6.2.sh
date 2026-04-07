#!/bin/bash
for dossier in "$@"; do
    echo "--- Analyse de $dossier ---"
    # -type f (fichiers), -size +1M (plus de 1Mo), -printf (formatage)
    find "$dossier" -maxdepth 1 -type f -size +1M -printf "Fichier: %f | Taille: %s octets | UID: %u\n"
done