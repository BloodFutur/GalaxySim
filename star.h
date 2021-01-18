#ifndef STAR_H
#define STAR_H

#include "vector.h"
#include <GLES3/gl3.h>
#include <QOpenGLFunctions>
class Block;

class Star
{
public:
    using list = std::list<Star>;

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

    double mass;
    double density;

    void updatePosition(const double & step, bool verletIntegration);
    void updateSpeed(const double & step, const double & area);
    void updateAccelerationDensity(const Block & block, const double & precision);

    void operator=(const Star & star);
};

void initializeGalaxy(Star::list & galaxy, const int & starsNumber, const double & area,
                      const double & speedInit, const double & step,
                      bool isBlackHole, const double & blackHoleMass,
                      const double & galaxyThickness);

#endif // STAR_H
