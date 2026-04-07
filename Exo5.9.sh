#!/bin/bash

# Création des "sémaphores" via FIFO
mkfifo /tmp/fifo_vide
mkfifo /tmp/fifo_plein

# Initialisation : on dépose un jeton dans "vide" pour que l'émetteur commence
echo "go" > /tmp/fifo_vide &

# Émetteur
(
    for i in {A..E}; do
        read _ < /tmp/fifo_vide # Attend que la boîte soit vide
        echo "$i" > /tmp/boite_mail
        echo "Émetteur : J'ai déposé l'octet $i"
        echo "prêt" > /tmp/fifo_plein # Signale au récepteur
        sleep $((1 + RANDOM % 3))
    done
) &

# Récepteur
(
    for i in {1..5}; do
        read _ < /tmp/fifo_plein # Attend que la boîte soit pleine
        octet=$(cat /tmp/boite_mail)
        echo "Récepteur : J'ai lu l'octet $octet"
        echo "vide" > /tmp/fifo_vide # Signale à l'émetteur
        sleep $((1 + RANDOM % 3))
    done
) &

wait
rm /tmp/fifo_vide /tmp/fifo_plein /tmp/boite_mail