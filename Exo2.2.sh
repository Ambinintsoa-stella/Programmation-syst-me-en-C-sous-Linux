#!/bin/bash
(echo "je suis le fils 1") &
(echo "je suis le fils 2") &
echo "je suis le père"
wait