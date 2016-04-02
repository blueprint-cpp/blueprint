#!/bin/bash

if [[ $(uname) == "Darwin" ]]; then

    package=sqlite3

    echo brew install $package
    brew install $package
    echo -en "\n"

elif [[ -z ${TRAVIS} ]]; then

    package="libsqlite3-dev"

    echo apt-get install $package
    sudo apt-get -yq --force-yes install $package
    echo -en "\n"

fi
