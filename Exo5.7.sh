#!/bin/bash
u=1.0
compt=0

# On utilise un fichier pour simuler la mémoire partagée entre processus
echo "$u" > u_val.txt
echo "$compt" > count.txt

f1() {
    while true; do
        flock u_val.txt -c '
            curr=$(cat u_val.txt)
            c=$(cat count.txt)
            new=$(echo "scale=4; ($curr-1)^2/4" | bc)
            echo "$new" > u_val.txt
            echo $((c+1)) > count.txt
            echo "[T1] u=$new (iter=$((c+1)))"
        '
        sleep $((RANDOM % 5 + 1))
    done
}

f2() {
    while true; do
        flock u_val.txt -c '
            curr=$(cat u_val.txt)
            c=$(cat count.txt)
            new=$(echo "scale=4; ($curr-2)^2/6" | bc)
            echo "$new" > u_val.txt
            echo $((c+1)) > count.txt
            echo "[T2] u=$new (iter=$((c+1)))"
        '
        sleep $((RANDOM % 5 + 1))
    done
}

f1 & f2 &
wait