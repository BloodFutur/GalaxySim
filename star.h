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
    using list = std::list<Star>;

    struct range {
        list::iterator begin;
        list::iterator end;
    };

    Star();
    Star(const double & speedInit, const double & area, const double & step, const double & galaxy_thickness);
    Star(const Star & star);

    int index;
    int blockIndex;

    bool isAlive;
    Vector previousPosition;
    Vector position;
    Vector speed;
    Vector acceleration;

    Vector color = { 0.0, 0.0, 0.0};
    double mass;
    double density;

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
