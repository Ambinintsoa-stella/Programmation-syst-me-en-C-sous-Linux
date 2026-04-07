#!/bin/bash

# Simule le Thread 1
generer_tableau() {
    local n=$1
    local tab=()
    for ((i=0; i<n; i++)); do
        tab+=($((RANDOM % 100)))
    done
    echo "${tab[@]}" > /tmp/shared_tab.txt
}

read -p "Nombre d'éléments : " n
generer_tableau $n & # Lancement en arrière-plan
pid_gen=$!

read -p "Entrez x : " x

wait $pid_gen # Attendre la fin de la génération
mon_tab=($(cat /tmp/shared_tab.txt))

# Simule le Thread 2 (Recherche)
trouve=0
for val in "${mon_tab[@]}"; do
    if [ "$val" -eq "$x" ]; then trouve=1; break; fi
done

echo "Résultat : $trouve"
rm /tmp/shared_tab.txt