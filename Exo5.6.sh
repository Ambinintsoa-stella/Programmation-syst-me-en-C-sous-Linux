#!/bin/bash
# Initialisation du tableau dans un fichier
for i in {0..99}; do
    if [[ $i -eq 0 || $i -eq 99 ]]; then echo "0" >> tab.txt
    else echo $((RANDOM % 101)) >> tab.txt; fi
done

# Thread Calcul
(
    while true; do
        # Simulation Mutex par verrou de fichier
        flock tab.txt -c '
            mapfile -t arr < tab.txt
            for i in {1..98}; do
                prev=${arr[$((i-1))]}
                curr=${arr[$i]}
                next=${arr[$((i+1))]}
                arr[$i]=$(echo "scale=2; ($prev+$curr+$next)/3" | bc)
            done
            printf "%s\n" "${arr[@]}" > tab.txt
        '
        sleep $((RANDOM % 3 + 1))
    done
) &

# Thread Affichage
(
    while true; do
        sleep 4
        echo "Lecture du tableau..."
        head -n 5 tab.txt
    done
) &
wait