#include <iostream>
#include <iomanip>
#include <cmath>
#include "ThreeBody.h"

const double G = 6.67430e-11; // gravitational constant

ThreeBodySimulation::ThreeBodySimulation(const ThreeBody& threeBody, double dt, const std::string& filename)
    : bodies(threeBody), dt(dt), outputFile(filename) {
    if (!outputFile.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    outputFile << "time,body1_x,body1_y,body1_z,body2_x,body2_y,body2_z,body3_x,body3_y,body3_z\n";
}

ThreeBodySimulation::~ThreeBodySimulation() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

void ThreeBodySimulation::computeForces() {
    // Reset accelerations to zero
    bodies.body1.acceleration.fill(0.0);
    bodies.body2.acceleration.fill(0.0);
    bodies.body3.acceleration.fill(0.0);

    std::array<Body*, 3> bodyArray = {&bodies.body1, &bodies.body2, &bodies.body3};

    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            std::array<double, 3> diff;
            double dist = 0.0;
            for (int k = 0; k < 3; ++k) {
                diff[k] = bodyArray[j]->position[k] - bodyArray[i]->position[k];
                dist += diff[k] * diff[k];
            }
            dist = std::sqrt(dist);
            double force = (G * bodyArray[i]->mass * bodyArray[j]->mass) / (dist * dist * dist);
            for (int k = 0; k < 3; ++k) {
                double f = force * diff[k];
                bodyArray[i]->acceleration[k] += f / bodyArray[i]->mass;
                bodyArray[j]->acceleration[k] -= f / bodyArray[j]->mass;
            }
        }
    }
}

void ThreeBodySimulation::rungeKuttaFehlbergStep() {
    const double c2 = 1.0 / 4.0;
    const double c3 = 3.0 / 8.0;
    const double c4 = 12.0 / 13.0;
    const double c5 = 1.0;
    const double c6 = 1.0 / 2.0;

    const std::array<double, 5> b1 = {1.0 / 4.0, 3.0 / 32.0, 1932.0 / 2197.0, 439.0 / 216.0, -8.0 / 27.0};
    const std::array<double, 5> b2 = {0.0, 9.0 / 32.0, -7200.0 / 2197.0, -8.0, 2.0};
    const std::array<double, 5> b3 = {0.0, 0.0, 7296.0 / 2197.0, 3680.0 / 513.0, -3544.0 / 2565.0};
    const std::array<double, 5> b4 = {0.0, 0.0, 0.0, -845.0 / 4104.0, 1859.0 / 4104.0};
    const std::array<double, 5> b5 = {0.0, 0.0, 0.0, 0.0, 11.0 / 40.0};

    const std::array<double, 6> c = {0.0, c2, c3, c4, c5, c6};
    const std::array<double, 6> a = {0.0, 0.25, 3.0 / 8.0, 12.0 / 13.0, 1.0, 0.5};
    const std::array<double, 6> b = {16.0 / 135.0, 0.0, 6656.0 / 12825.0, 28561.0 / 56430.0, -9.0 / 50.0, 2.0 / 55.0};

    std::array<ThreeBody, 6> k;
    ThreeBody temp_positions;
    ThreeBody temp_velocities;

    for (int i = 0; i < 6; ++i) {
        if (i == 0) {
            computeForces();
            for (int j = 0; j < 3; ++j) {
                k[i].body1.position[j] = dt * bodies.body1.velocity[j];
                k[i].body2.position[j] = dt * bodies.body2.velocity[j];
                k[i].body3.position[j] = dt * bodies.body3.velocity[j];
                k[i].body1.velocity[j] = dt * bodies.body1.acceleration[j];
                k[i].body2.velocity[j] = dt * bodies.body2.acceleration[j];
                k[i].body3.velocity[j] = dt * bodies.body3.acceleration[j];
            }
        } else {
            // Compute temporary positions and velocities
            for (int j = 0; j < 3; ++j) {
                temp_positions.body1.position[j] = bodies.body1.position[j];
                temp_positions.body2.position[j] = bodies.body2.position[j];
                temp_positions.body3.position[j] = bodies.body3.position[j];
                temp_velocities.body1.velocity[j] = bodies.body1.velocity[j];
                temp_velocities.body2.velocity[j] = bodies.body2.velocity[j];
                temp_velocities.body3.velocity[j] = bodies.body3.velocity[j];
                for (int l = 0; l < i; ++l) {
                    temp_positions.body1.position[j] += a[l] * k[l].body1.position[j];
                    temp_positions.body2.position[j] += a[l] * k[l].body2.position[j];
                    temp_positions.body3.position[j] += a[l] * k[l].body3.position[j];
                    temp_velocities.body1.velocity[j] += a[l] * k[l].body1.velocity[j];
                    temp_velocities.body2.velocity[j] += a[l] * k[l].body2.velocity[j];
                    temp_velocities.body3.velocity[j] += a[l] * k[l].body3.velocity[j];
                }
            }
            computeForces();
            for (int j = 0; j < 3; ++j) {
                k[i].body1.position[j] = dt * temp_velocities.body1.velocity[j];
                k[i].body2.position[j] = dt * temp_velocities.body2.velocity[j];
                k[i].body3.position[j] = dt * temp_velocities.body3.velocity[j];
                k[i].body1.velocity[j] = dt * bodies.body1.acceleration[j];
                k[i].body2.velocity[j] = dt * bodies.body2.acceleration[j];
                k[i].body3.velocity[j] = dt * bodies.body3.acceleration[j];
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        bodies.body1.position[i] += b[0] * k[0].body1.position[i] + b[1] * k[1].body1.position[i] + b[2] * k[2].body1.position[i] + b[3] * k[3].body1.position[i] + b[4] * k[4].body1.position[i] + b[5] * k[5].body1.position[i];
        bodies.body2.position[i] += b[0] * k[0].body2.position[i] + b[1] * k[1].body2.position[i] + b[2] * k[2].body2.position[i] + b[3] * k[3].body2.position[i] + b[4] * k[4].body2.position[i] + b[5] * k[5].body2.position[i];
        bodies.body3.position[i] += b[0] * k[0].body3.position[i] + b[1] * k[1].body3.position[i] + b[2] * k[2].body3.position[i] + b[3] * k[3].body3.position[i] + b[4] * k[4].body3.position[i] + b[5] * k[5].body3.position[i];

        bodies.body1.velocity[i] += b[0] * k[0].body1.velocity[i] + b[1] * k[1].body1.velocity[i] + b[2] * k[2].body1.velocity[i] + b[3] * k[3].body1.velocity[i] + b[4] * k[4].body1.velocity[i] + b[5] * k[5].body1.velocity[i];
        bodies.body2.velocity[i] += b[0] * k[0].body2.velocity[i] + b[1] * k[1].body2.velocity[i] + b[2] * k[2].body2.velocity[i] + b[3] * k[3].body2.velocity[i] + b[4] * k[4].body2.velocity[i] + b[5] * k[5].body2.velocity[i];
        bodies.body3.velocity[i] += b[0] * k[0].body3.velocity[i] + b[1] * k[1].body3.velocity[i] + b[2] * k[2].body3.velocity[i] + b[3] * k[3].body3.velocity[i] + b[4] * k[4].body3.velocity[i] + b[5] * k[5].body3.velocity[i];
    }
}

void ThreeBodySimulation::update() {
    static double time = 0;
    rungeKuttaFehlbergStep();
    writeToCSV(time);
    time += dt;
}

void ThreeBodySimulation::printPositions() const {
    std::cout << "Body 1 Position: (" << bodies.body1.position[0] << ", " << bodies.body1.position[1] << ", " << bodies.body1.position[2] << ")\n";
    std::cout << "Body 2 Position: (" << bodies.body2.position[0] << ", " << bodies.body2.position[1] << ", " << bodies.body2.position[2] << ")\n";
    std::cout << "Body 3 Position: (" << bodies.body3.position[0] << ", " << bodies.body3.position[1] << ", " << bodies.body3.position[2] << ")\n";
}

const ThreeBody& ThreeBodySimulation::getBodies() const {
    return bodies;
}

void ThreeBodySimulation::writeToCSV(double time) const {
    outputFile << std::fixed << std::setprecision(8) << time << ','
               << bodies.body1.position[0] << ',' << bodies.body1.position[1] << ',' << bodies.body1.position[2] << ','
               << bodies.body2.position[0] << ',' << bodies.body2.position[1] << ',' << bodies.body2.position[2] << ','
               << bodies.body3.position[0] << ',' << bodies.body3.position[1] << ',' << bodies.body3.position[2] << '\n';
}
