#!/bin/bash
# Le "père" lance une commande, le "fils" (grep) reçoit le flux
echo "mot1 mot2 cible mot3" | grep "cible"