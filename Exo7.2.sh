# Affiche.sh
echo "PID: $$"
trap 'cat /tmp/entier.txt; echo' SIGUSR1
while true; do sleep 1; done

# Saisit.sh (dans un autre terminal)
read -p "Entier : " n
echo $n > /tmp/entier.txt
kill -USR1 [PID_DE_AFFICHE]