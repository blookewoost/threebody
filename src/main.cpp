#include <iostream>
#include "lib.h"
#include "ThreeBody.h"

int main() {

    ThreeBody test = consume_ini("../data/special.ini");
    double dt = 86400; // 1 day time step
    ThreeBodySimulation sim(test, dt, "../data/results.csv");

    for (int i = 0; i < 1000; ++i) {
        sim.update();
    }

    return 0;
}
