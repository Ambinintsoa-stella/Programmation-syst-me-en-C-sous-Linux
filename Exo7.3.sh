#!/bin/bash

# Création des 5 fils
pids=()
for i in {0..4}; do
    (
        # Code du fils : définit son propre message de mort
        trap "echo -e '\n[Fils $i (PID: $$)] : On me tue ! Adieu...'; exit" SIGTERM
        while true; do sleep 1; done
    ) &
    pids[$i]=$!
done

# Message de mort pour le père
trap "echo '[PÈRE] : Je disparais aussi...'; exit" SIGTERM

while true; do
    echo -e "\n--- GESTION DES FILS ---"
    echo "Fils disponibles : ${pids[@]}"
    read -p "Numéro du fils (0-4) et Action (s:stop, r:reprendre, t:terminer, q:quitter) : " num action
    
    target=${pids[$num]}

    case $action in
        s) kill -STOP $target ;;
        r) kill -CONT $target ;;
        t) kill -TERM $target ;;
        q) 
           for p in "${pids[@]}"; do kill -TERM $p 2>/dev/null; done
           exit 0 ;;
        *) echo "Action inconnue" ;;
    esac
done