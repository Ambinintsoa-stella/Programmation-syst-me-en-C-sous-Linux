#!/bin/bash
# Nettoyage des anciens jetons
rm -f /tmp/rdv_t1 /tmp/rdv_t2

# Thread 1
(
    for i in {1..10}; do
        sleep 2
        echo "T1 prêt ($i)"
        touch /tmp/rdv_t1 # Signale sa présence
        while [ ! -f /tmp/rdv_t2 ]; do sleep 0.1; done # Attend T2
        echo "T1 franchit le rendez-vous $i"
        rm -f /tmp/rdv_t1
        sleep 0.5 # Petit délai pour laisser T2 nettoyer son fichier
    done
) &

# Thread 2
(
    for i in {1..10}; do
        sleep $((4 + RANDOM % 6))
        echo "T2 prêt ($i)"
        touch /tmp/rdv_t2 # Signale sa présence
        while [ ! -f /tmp/rdv_t1 ]; do sleep 0.1; done # Attend T1
        echo "T2 franchit le rendez-vous $i"
        rm -f /tmp/rdv_t2
    done
) &

wait