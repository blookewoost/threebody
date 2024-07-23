#include <iostream>
#include "lib.h"
#include "ThreeBody.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Invalid arguments detected. Usage: ./threebody <filename>\n");
        return 1;
    }

    const char* filename = argv[1];

    ThreeBody test = consume_ini(filename);
    double dt = 86400; // 1 day time step
    ThreeBodySimulation sim(test, dt, "./data/results.csv");

    for (int i = 0; i < 1000; ++i) {
        sim.update();
    }

    return 0;
}
