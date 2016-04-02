#!/bin/bash

if [[ $(uname) == "Darwin" ]]; then
    sqlite=sqlite3

    echo brew install $sqlite
    brew install $sqlite
    echo -en "\n"
fi
