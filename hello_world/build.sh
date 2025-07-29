#!/bin/bash
set -e


# Build script for hello_world.cpp
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
SRC="$SCRIPT_DIR/hello_world.cpp"
OUT="$SCRIPT_DIR/hello_world"

echo "Compiling $SRC..."
clang++ -std=c++23 -g "$SRC" -o "$OUT"
echo "Build complete: $OUT"