#!/bin/bash
# Création d'un tube nommé pour la réponse
mkfifo /tmp/rep_pipe

read -p "Entrez le mot à chercher : " mot

# Le père (processus en arrière-plan) fait la recherche
(
    if grep -qw "$mot" "dictionnaire.txt"; then
        echo 1 > /tmp/rep_pipe
    else
        echo 0 > /tmp/rep_pipe
    fi
) &

# Le fils lit la réponse
resultat=$(cat /tmp/rep_pipe)
if [ "$resultat" -eq 1 ]; then
    echo "Mot trouvé !"
else
    echo "Mot absent."
fi

rm /tmp/rep_pipe