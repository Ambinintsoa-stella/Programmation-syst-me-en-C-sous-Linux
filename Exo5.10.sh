#!/bin/bash
mkfifo /tmp/tampon

# Producteur
(
    while true; do
        echo "OBJET" > /tmp/tampon
        echo "[Prod] Objet envoyé"
        sleep $((RANDOM % 3 + 1))
    done
) &

# Consommateur
(
    while true; do
        read msg < /tmp/tampon
        echo "[Cons] Objet reçu"
        sleep $((RANDOM % 3 + 1))
    done
) &

wait