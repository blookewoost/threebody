#ifndef THREE_BODY_H
#define THREE_BODY_H

#include <array>

struct Body {
    double mass;
    std::array<double, 3> position;
    std::array<double, 3> velocity;
    std::array<double, 3> acceleration;
};

struct ThreeBody {
    Body body1;
    Body body2;
    Body body3;
};

class ThreeBodySimulation {
public:
    ThreeBodySimulation(const ThreeBody& threeBody, double dt);
    void update();
    void printPositions() const;

private:
    double dt; // initial time step
    ThreeBody bodies;
    void computeForces();
    void rungeKuttaFehlbergStep();
};

#endif // THREE_BODY_H
