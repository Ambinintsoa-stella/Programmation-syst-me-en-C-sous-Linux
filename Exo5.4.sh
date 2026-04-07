#!/bin/bash

# Simulation de l'annulation (en arrière-plan)
(
    while true; do
        read -n 1 key
        if [[ $key == "A" || $key == "a" ]]; then
            echo -e "\n[ANNULATION]"
            kill -9 $$ # Tue le script parent
        fi
    done
) &

t1=(1 2 3)
t2=(0 1 2 3 4 5)

echo "Vérification de l'inclusion..."
sleep 3 # Simulation de calcul long

inclus=true
for i in "${t1[@]}"; do
    found=false
    for j in "${t2[@]}"; do
        if [ "$i" -eq "$j" ]; then found=true; break; fi
    done
    if [ "$found" = false ]; then inclus=false; break; fi
done

echo "Inclusion : $inclus"