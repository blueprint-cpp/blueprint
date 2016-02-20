#!/bin/bash

pushd $(dirname $0) > /dev/null

premake=buildtools-premake/bin/premake.sh

$premake gmake
r=$?

if [[ $r -eq 0 ]]; then
    cd gmake

    make
    r=$?
fi

popd > /dev/null

exit $r
