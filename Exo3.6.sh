#!/bin/bash

n=$1
k=$2

# Cas de base : Ci0 = 1 et Cii = 1
if [ "$k" -eq 0 ] || [ "$k" -eq "$n" ]; then
    echo 1
    exit 0
fi

# Pour simuler la récursion sans fonction, le script s'appelle lui-même ($0)
# On utilise des sous-shells (...) pour récupérer les résultats
val1=$($0 $((n-1)) $((k-1)))
val2=$($0 $((n-1)) $k)

# Addition des deux résultats
echo $((val1 + val2))