#!/bin/bash

pushd $(dirname $0) > /dev/null

if [[ ! -d "store" ]]; then mkdir store; fi
cd store

premake_url="http://github.com/premake/premake-core/releases/download/v5.0.0-alpha8/premake-5.0.0-alpha8-macosx.tar.gz"
premake_file="premake-5.0.0-alpha8-macosx.tar.gz"
premake_dir="premake"

if [[ ! -e $premake_file ]]; then wget --no-check-certificate $premake_url; fi

if [[ ! -d $premake_dir ]]; then
    mkdir $premake_dir
    tar -xvf $premake_file -C $premake_dir
fi

popd > /dev/null
