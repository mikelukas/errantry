#!/bin/sh

#determine actual location of errantry binary (readlink will resolve any symlinks to the launch script)
ERRANTRY_DIR=$(dirname `readlink $0`)

#Change dir to be relative to errantry binary so it can find its dat folder; otherwise it will look relative to its symlink
pushd $ERRANTRY_DIR > /dev/null

clear
$ERRANTRY_DIR/errantry

popd > /dev/null
