#!/bin/bash
# Le fils accède à la variable TUBE_PATH définie par le père
if [ -n "$TUBE_PATH" ]; then
    read message < "$TUBE_PATH"
    echo "Fils a reçu : $message"
fi