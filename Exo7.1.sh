#!/bin/bash
# Lancement d'un calcul infini en arrière-plan
( while true; do echo "Calcul..."; sleep 1; done ) &
pid=$!

while true; do
    read -p "Menu: (s)top, (r)esume, (q)uit: " choix
    case $choix in
        s) kill -STOP $pid ;;
        r) kill -CONT $pid ;;
        q) kill -TERM $pid; break ;;
    esac
done