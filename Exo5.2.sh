#!/bin/bash

genere_tableau() {
    local tab=()
    for i in {1..5}; do
        tab+=($((RANDOM % 100)))
    done
    echo "${tab[@]}" # "Renvoie" les données via la sortie standard
}

echo "Main : Attente du tableau..."

# On capture le résultat du processus fils
resultat=$(genere_tableau)

echo "Main : Valeurs reçues : $resultat"