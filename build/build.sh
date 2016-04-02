#!/bin/bash

pushd $(dirname $0) > /dev/null

./generate.sh
r=$?

if [[ $r -eq 0 ]]; then
    cd gmake

    make
    r=$?
fi

popd > /dev/null

exit $r
