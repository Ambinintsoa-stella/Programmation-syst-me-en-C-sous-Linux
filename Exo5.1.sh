#!/bin/bash

# "Fonction" simulant le thread
affiche_tableau() {
    local tab=("$@") # Récupère tous les arguments dans un tableau
    echo -n "Contenu du tableau (processus fils) : "
    echo "${tab[@]}"
}

mon_tab=(10 20 30 40 50)

# Lancement en arrière-plan (simule le parallélisme)
affiche_tableau "${mon_tab[@]}" &

wait # Attente de la fin du processus fils