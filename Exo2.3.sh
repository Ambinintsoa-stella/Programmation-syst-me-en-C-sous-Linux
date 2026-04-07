#!/bin/bash
for i in {1..5}
do
    (echo "Processus fils créé") &
done
wait