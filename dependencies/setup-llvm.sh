#!/bin/bash

if [[ $(uname) == "Darwin" ]]; then
    llvm=llvm38

    echo brew install $llvm
    brew install $llvm
    echo -en "\n"
fi
