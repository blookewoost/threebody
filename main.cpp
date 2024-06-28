#include <iostream>
#include "ThreeBody.h"

int main() {
    Body body1 = {5.972e24, {1e11, 0, 0}, {0, 30000, 0}}; // Earth
    Body body2 = {7.348e22, {1e11 + 384400000, 0, 0}, {0, 30000 + 1022, 0}}; // Moon
    Body body3 = {1.989e30, {0, 0, 0}, {0, 0, 0}}; // Sun

    ThreeBody threeBody = {body1, body2, body3};
    double dt = 86400; // 1 day time step
    ThreeBodySimulation sim(threeBody, dt, "three_body_simulation.csv");

    for (int i = 0; i < 1000; ++i) {
        sim.update();
        sim.printPositions();
    }

    return 0;
}
