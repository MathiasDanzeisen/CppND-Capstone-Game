#!/bin/bash -v

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Add repo path to env so images are found
export PATH="${SCRIPT_DIR}:$PATH"

${SCRIPT_DIR}/build/Game
