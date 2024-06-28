#include <iostream>
#include "ThreeBody.h"

int main() {
    Body body1 = {5.972e28, {1e11, -1e11, -1e11}, {0, 1000, 1000}};
    Body body2 = {7.348e28, {0, 1e11, 0}, {0, -1000, 0}};
    Body body3 = {1.989e30, {-1e11, 0, 1e11}, {10000, -1000, 0}};

    ThreeBody threeBody = {body1, body2, body3};
    double dt = 86400; // 1 day time step
    ThreeBodySimulation sim(threeBody, dt, "three_body_simulation.csv");

    for (int i = 0; i < 1000; ++i) {
        sim.update();
        sim.printPositions();
    }

    return 0;
}
