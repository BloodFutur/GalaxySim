#ifndef STAR_H
#define STAR_H

#include "vector.h"
#include <GLES3/gl3.h>
#include <QOpenGLFunctions>
class Block;

// TODO Comment this class

// This class defines a Star in the galaxy

class Star
{
public:
    using list = std::vector<Star>;

    struct range {
        list::iterator begin;
        list::iterator end;
    };

    Star() = default;
    virtual ~Star() = default;

    Star(const double & speedInit, const double & area, const double & step, const double & galaxy_thickness);
    Star(const Star & star) = default;

    int index {0};
    int blockIndex {0};

    bool isAlive{false};
    Vector previousPosition{0,0,0};
    Vector position{ 0, 0, 0};
    Vector speed{ 0, 0, 0};
    Vector acceleration{ 0, 0, 0};

    Vector color = { 0.0, 0.0, 0.0};
    double mass {0};
    double density {0};

    void updatePosition(const double & step, bool verletIntegration);
    void updateSpeed(const double & step, const double & area);
    void updateAccelerationDensity(const Block & block, const double & precision);
    void updateColor(); // Compared to the density

    void operator=(const Star & star);
};


void initializeGalaxy(Star::list & galaxy, const int & starsNumber, const double & area,
                      const double & speedInit, const double & step,
                      bool isBlackHole, const double & blackHoleMass,
                      const double & galaxyThickness);

// Compute density and force applied on a star
Vector forceDensityCalculations(const Block& block, Star & star, const double & precision);

#endif // STAR_H
