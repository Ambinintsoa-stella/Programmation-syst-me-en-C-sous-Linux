#!/bin/bash
while true; do
    read -p "Destination (ou 'q' pour quitter) : " dest
    if [ "$dest" == "q" ]; then break; fi
    cp -r . "$dest"
done