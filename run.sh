#!/bin/bash

BIN_PATH="./bin/threebody"
DATA_FILE="./data/results.csv"

# Execute the makefile and generate a binary.
compile_simulation() {
    echo -e "Binary not found, compiling..."
    make -C bin
}

# Run the simulation and check to see if a results file was generated.
run_simulation() {
    echo -e "Running Three-Body-Problem Simulation..."
    "$BIN_PATH"
    if [ -f "$DATA_FILE" ]; then
        echo -e "Complete!"
    else
        echo -e "Something went wrong, and the simulation did not generate a results file!"
    fi
}


# main
if [ -f "$BIN_PATH" ]; then
    run_simulation
else
    compile_simulation
    run_simulation
fi




