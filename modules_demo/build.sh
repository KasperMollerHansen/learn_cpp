#!/bin/bash
set -e
SOURCE_DIR="$(cd "$(dirname "$0")"; pwd)"
rm -rf "$SOURCE_DIR/build"
mkdir "$SOURCE_DIR/build"
cd "$SOURCE_DIR/build"
cmake -G Ninja "$SOURCE_DIR"
ninja
"$SOURCE_DIR/run.sh"