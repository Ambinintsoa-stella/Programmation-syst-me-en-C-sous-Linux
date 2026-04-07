#!/bin/bash
# On crée un tube (via un fichier temporaire pour l'exemple)
mkfifo /tmp/mon_pipe

# On stocke le chemin dans une variable d'environnement
export TUBE_PATH="/tmp/mon_pipe"

# On lance le processus d'écriture en arrière-plan
echo "Donnée via ENV" > $TUBE_PATH &

# On lance le script fils
./fils_env_script.sh

rm /tmp/mon_pipe