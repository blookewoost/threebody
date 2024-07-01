#include <iostream>
#include "lib.h"
#include "ThreeBody.h"

int main() {

    ThreeBody test = consume_ini("example_ini.ini");

    // Body body1 = {5.972e28, {1e11, -1e11, -1e11}, {0, 1000, 1000}};
    // Body body2 = {7.348e28, {0, 1e11, 0}, {0, -1000, 0}};
    // Body body3 = {1.989e30, {-1e11, 0, 1e11}, {10000, -1000, 0}};
// 
    // ThreeBody threeBody = {body1, body2, body3};
    double dt = 86400; // 1 day time step
    ThreeBodySimulation sim(test, dt, "three_body_simulation.csv");

    for (int i = 0; i < 1000; ++i) {
        sim.update();
    }

    return 0;
}
