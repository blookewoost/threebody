#ifndef THREE_BODY_H
#define THREE_BODY_H

#include <array>
#include <fstream>

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
    ThreeBodySimulation(const ThreeBody& threeBody, double dt, const std::string& filename);
    ~ThreeBodySimulation();
    void update();
    void printPositions() const;
    const ThreeBody& getBodies() const;
    void writeToCSV(double time) const;

private:
    double dt; // initial time step
    ThreeBody bodies;
    mutable std::ofstream outputFile;
    void computeForces();
    void rungeKuttaFehlbergStep();
};

#endif // THREE_BODY_H
