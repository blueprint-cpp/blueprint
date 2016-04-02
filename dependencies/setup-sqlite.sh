#!/bin/bash

if [[ $(uname) == "Darwin" ]]; then
    if [[ ! $1 == "skip-update" ]]; then
        echo brew update
        brew update
        echo -en "\n"
    fi

    sqlite=sqlite3

    echo brew install $sqlite
    brew install $sqlite
    echo -en "\n"
fi
