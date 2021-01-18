#include "star.h"
#include "vector.h"
#include "utils.h"

Star::Star()
{
    index = 0;
    blockIndex = 0;
    isAlive = false;
    previousPosition = Vector(0., 0., 0.);
    position  = Vector(0., 0., 0.);
    speed =  Vector(0., 0., 0.);
    acceleration  = Vector(0., 0., 0.);
    mass = 0.;
    density = 0.;
}

Star::Star(const double &speedInit, const double &area, const double &step, const double &galaxy_thickness)
{
    index = 0;
    blockIndex = 0;
    isAlive = true;
    position = Vector::createSpherical((sqrt(random(0.,1.)) - 0.5) * area, random(0., 2. * PI), PI / 2);
    position.z(((random(0.,1.) - 0.5) * (area * galaxy_thickness)));
    speed = Vector::createSpherical(speedInit, position.getPhi() + PI / 2., PI / 2);
    previousPosition = position - (speed * step);
    acceleration = Vector(0., 0., 0.);
    mass = 0.;
    density = 0.;
}

Star::Star(const Star &star)
{
    index = star.index;
    blockIndex = star.blockIndex;
    isAlive = star.isAlive;
    position = star.position;
    speed = star.speed;
    previousPosition = star.previousPosition;
    acceleration = star.acceleration;
    mass = star.mass;
    density = star.density;
}

void Star::updatePosition(const double &step, bool verletIntegration)
{
    if(!verletIntegration)
        position += speed * step; // Euler's method
    else {
        Vector t = position;
        position = 2. * position - previousPosition + acceleration * step * step; // Verlet Integration
        previousPosition = t;
    }
}

void Star::updateSpeed(const double &step, const double &area)
{
    speed += step * acceleration;
}
