#!/bin/bash

while true; do
    # Demander le nom du fichier à l'utilisateur
    read -p "Fichier à ouvrir (ou 'q' pour quitter) : " fichier
    
    # Vérifier si l'on doit quitter
    if [ "$fichier" == "q" ]; then
        break
    fi

    # Lancer emacs. 
    # Contrairement au C (exec), le script Bash attend que l'éditeur 
    # soit fermé avant de continuer la boucle.
    /usr/bin/emacs "$fichier"
done