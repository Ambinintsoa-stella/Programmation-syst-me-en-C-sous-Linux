#!/bin/bash

# Initialisation
echo "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" > base_donnees.txt
echo "0" > nb_lecteurs.txt
touch verrou_base.lock

# Fonction Lecteur
lecteur() {
    local id=$1
    while true; do
        # --- Entrée Section Critique Lecteur ---
        flock nb_lecteurs.txt -c '
            read n < nb_lecteurs.txt
            n=$((n + 1))
            echo $n > nb_lecteurs.txt
            if [ $n -eq 1 ]; then
                # Le premier lecteur prend le verrou global contre les rédacteurs
                flock --wait 10 verrou_base.lock true
            fi
        '
        
        # --- Lecture ---
        pos=$((RANDOM % 15))
        val=$(awk -v p=$((pos+1)) '{print $p}' base_donnees.txt)
        echo "Lecteur $id lit à la pos $pos : $val"
        sleep $((1 + RANDOM % 3))

        # --- Sortie Section Critique Lecteur ---
        flock nb_lecteurs.txt -c '
            read n < nb_lecteurs.txt
            n=$((n - 1))
            echo $n > nb_lecteurs.txt
            if [ $n -eq 0 ]; then
                # Le dernier lecteur libère le verrou pour les rédacteurs
                # (Dans une vraie simulation flock, le verrou est libéré à la fin du bloc)
            fi
        '
        sleep $((1 + RANDOM % 3))
    done
}

# Fonction Rédacteur
redacteur() {
    local id=$1
    while true; do
        echo "Rédacteur $id attend pour écrire..."
        # Le rédacteur essaie de prendre le verrou exclusif
        flock verrou_base.lock -c "
            pos=\$((RANDOM % 15))
            nouveau_val=\$((RANDOM % 100))
            # Mise à jour de la base (simulation atomique via sed)
            sed -i \"s/\([^ ]* \)\{$pos\}\([^ ]*\)/\1$nouveau_val/\" base_donnees.txt
            echo \"!!! RÉDACTEUR $id a écrit $nouveau_val à la pos $pos !!!\"
            sleep $((2 + RANDOM % 4))
        "
        sleep $((5 + RANDOM % 6))
    done
}

# Lancement des processus
for i in {1..3}; do lecteur $i & done
for i in {1..2}; do redacteur $i & done

wait