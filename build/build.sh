#!/bin/bash

pushd $(dirname $0) > /dev/null

START=$(date +%s)

./generate.sh
r=$?

if [[ $r -eq 0 ]]; then
    cd gmake

    make
    r=$?
fi

END=$(date +%s)
DIFF=$(( $END - $START ))
echo "Build Time: $DIFF seconds"

popd > /dev/null

exit $r
