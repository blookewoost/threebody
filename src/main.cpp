#include <iostream>
#include "lib.h"
#include "ThreeBody.h"

int main(int argc, char* argv[]) {

    ThreeBody test = consume_ini("./data/ic.ini");
    double dt = 86400; // 1 day time step
    ThreeBodySimulation sim(test, dt, "./data/results.csv");

    for (int i = 0; i < 1000; ++i) {
        sim.update();
    }

    return 0;
}
