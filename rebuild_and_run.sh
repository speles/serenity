#!/bin/bash
set -e

if [[ "$1 $2 $3" = *"toolchain"* ]] ; then
    rm -rf ./Build ./build ./Toolchain/Build ./Toolchain/Local ./Toolchain/build

    cd Toolchain
    ./BuildIt.sh
    cd ..
fi

mkdir -p ./Build
cd Build

if [[ "$1 $2 $3" = *"full"* ]] ; then
    cmake .. -G Ninja
fi

ninja
ninja install

if [[ ! "$1 $2 $3" = *"norun"* ]] ; then
    ninja image
    ninja run
fi
