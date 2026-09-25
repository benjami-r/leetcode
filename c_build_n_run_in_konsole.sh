#!/bin/bash
# cmake --build --preset debug && konsole --profile dur -e bash -lc "./build/$(basename "$PWD"); echo; echo 'Process finished. Press any key to close...'; read -n 1" 2>/dev/null
cmake --build --preset debug --target run_in_konsole
