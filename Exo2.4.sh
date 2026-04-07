#!/bin/bash
for i in {1..5}
do
    (echo "je suis le fils $i") &
done
wait