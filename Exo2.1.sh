#!/bin/bash
# Le "&" lance la commande dans un nouveau processus (fils)
(echo "je suis le fils") & 
echo "je suis le père"
wait # Attendre que le fils termine