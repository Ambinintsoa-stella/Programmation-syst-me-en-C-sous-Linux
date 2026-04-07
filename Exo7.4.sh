#!/bin/bash

read -p "Taille du tableau : " n
# Création d'un tableau simulé
tab=()
for ((i=0; i<n; i++)); do tab[$i]=$((i * 10)); done

while true; do
    read -p "Entrez l'index à afficher : " idx

    # Simulation de la détection d'erreur (équivalent logique du SIGSEGV)
    if [[ ! "$idx" =~ ^[0-9]+$ ]] || [ "$idx" -ge "$n" ] || [ "$idx" -lt 0 ]; then
        echo "ERREUR DE SEGMENTATION (Index invalide : $idx)"
        echo "Tentative de récupération... Veuillez recommencer."
        continue # Équivalent du siglongjmp : on repart au début de la boucle
    else
        echo "Valeur à l'index $idx : ${tab[$idx]}"
        break
    fi
done