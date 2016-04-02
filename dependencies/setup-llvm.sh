#!/bin/bash

if [[ $(uname) == "Darwin" ]]; then
    if [[ ! $1 == "skip-update" ]]; then
        echo brew update
        brew update
        echo -en "\n"
    fi

    llvm=llvm38

    echo brew install $llvm
    brew install $llvm
    echo -en "\n"
fi
