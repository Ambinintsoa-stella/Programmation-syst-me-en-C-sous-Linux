#!/bin/bash
debut=$(date +%s)

for i in 1 2
do
    (
        duree=$((1 + RANDOM % 10))
        sleep $duree
        echo "Fils $i a dormi $duree sec"
    ) &
done

wait
fin=$(date +%s)
echo "Durée totale : $((fin - debut)) secondes"