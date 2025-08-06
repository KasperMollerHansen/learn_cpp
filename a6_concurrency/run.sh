#!/bin/bash
set -e
BIN_DIR="$(dirname "$0")/bin"
FIRST_EXEC=$(find "$BIN_DIR" -maxdepth 1 -type f -executable | head -n 1)
if [ -z "$FIRST_EXEC" ]; then
  echo "No executable found in $BIN_DIR"
  exit 1
fi
"$FIRST_EXEC" "$@"
