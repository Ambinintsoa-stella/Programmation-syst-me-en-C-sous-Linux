#!/bin/bash
echo 0 > compteur.txt
limite=$1

# Thread 1 : Incrémenteur
(
    while true; do
        val=$(cat compteur.txt)
        if [ $val -ge $limite ]; then break; i
        echo $((val + 1)) > compteur.txt
        sleep $((1 + RANDOM % 5))
    done
) &

# Thread 2 : Afficheur
(
    while true; do
        sleep 2
        val=$(cat compteur.txt)
        echo "Valeur : $val"
        if [ $val -ge $limite ]; then break; fi
    done
) &
wait
rm compteur.txt