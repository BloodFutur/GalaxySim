#include "star.h"
#include "vector.h"
#include "utils.h"
#include "block.h"


Star::Star(const double &speedInit, const double &area, const double &step, const double &galaxy_thickness)
{
    index = 0;
    blockIndex = 0;
    isAlive = true;
    position = Vector::createSpherical((sqrt(random(0.,1.)) - 0.5) * area, random(0., 2. * PI), PI * .5);
    position.z(((random(0.,1.) - 0.5) * (area * galaxy_thickness)));
    speed = Vector::createSpherical(speedInit, position.getPhi() + PI * 0.5, PI * 0.5);
    previousPosition = position - (speed * step);
    acceleration = Vector(0., 0., 0.);
    mass = 0.;
    density = 0.;
}

/*
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
*/

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

void Star::updateAccelerationDensity(const Block &block, const double &precision)
{
    density = 0;
    double maxAcceleration =  0.0000000005;
    acceleration = forceDensityCalculations(block, *this, precision);

    if(acceleration.getRadius() > maxAcceleration)
        acceleration = maxAcceleration * normalize(acceleration);
}

void Star::updateColor()
{
    int icolor = density * 5.;
    int R, G, B;
    if(icolor > 3 * 255) icolor = 3*255;
    if(icolor < 255) {
        R = 0;
        G = 0;
        B = icolor;
    } else if (icolor < 255*2) {
        R = 0;
        G = icolor - 255;
        B = 255;
    } else {
        R = icolor - 255*2;
        G = 255;
        B = 255;
    }
    color = Vector(R,G,B);
}

void Star::operator=(const Star &star)
{
    index = star.index;
    blockIndex = star.blockIndex;
    isAlive = star.isAlive;
    previousPosition = star.previousPosition;
    position = star.position;
    speed = star.speed;
    acceleration = star.acceleration;
    color = star.color;
    mass = star.mass;
    density = star.density;
}

void initializeGalaxy(Star::list &galaxy, const int &starsNumber, const double &area, const double &speedInit, const double &step, bool isBlackHole, const double &blackHoleMass, const double &galaxyThickness)
{
    for(int i{0}; i < starsNumber * 0.755; i++) {
        galaxy.emplace_back(Star(speedInit, area, step, galaxyThickness));
        galaxy.back().index = galaxy.size() - 1;
        galaxy.back().mass = random(0.08, .5) * SOLAR_MASS;
        galaxy.back().color = Vector(255, 10, 10);
    }
    for(int i{0}; i < starsNumber * 0.125; i++) {
        galaxy.emplace_back(Star(speedInit, area, step, galaxyThickness));
        galaxy.back().index = galaxy.size() - 1;
        galaxy.back().mass = random(.5, .8) * SOLAR_MASS;
        galaxy.back().color = Vector(255, 127, 10);
    }
    for(int i{0}; i < starsNumber * 0.08; i++) {
        galaxy.emplace_back(Star(speedInit, area, step, galaxyThickness));
        galaxy.back().index = galaxy.size() - 1;
        galaxy.back().mass = random(.8, 1.4) * SOLAR_MASS;
        galaxy.back().color = Vector(255, 255, 10);
    }
    for(int i{0}; i < starsNumber * 0.032; i++) {
        galaxy.emplace_back(Star(speedInit, area, step, galaxyThickness));
        galaxy.back().index = galaxy.size() - 1;
        galaxy.back().mass = random(1.4, 2.1) * SOLAR_MASS;
        galaxy.back().color = Vector(255, 255, 127);
    }
    for(int i{0}; i < starsNumber * 0.007; i++) {
        galaxy.emplace_back(Star(speedInit, area, step, galaxyThickness));
        galaxy.back().index = galaxy.size() - 1;
        galaxy.back().mass = random(2.1, 4.5) * SOLAR_MASS;
        galaxy.back().color = Vector(255, 255, 255);
    }
    for(int i{0}; i < starsNumber * 0.001; i++) {
        galaxy.emplace_back(Star(speedInit, area, step, galaxyThickness));
        galaxy.back().index = galaxy.size() - 1;
        galaxy.back().mass = random(4.5, 16.) * SOLAR_MASS;
        galaxy.back().color = Vector(50, 255, 255);
    }

}

Vector forceDensityCalculations(const Block &block, Star &star, const double &precision)
{
    Vector force = Vector(0., 0., 0.);
    Vector dStarMass = star.position - block.massCenter;
    double distance = getRadius(star.position, block.massCenter);

    if(block.nbStars == 1) {
        if(distance != 0.) {
            force += (dStarMass * (1. / distance)) * (-(G * block.mass) / (distance * distance));
            star.density += (1. / distance)  / (LIGHT_YEAR);
        }
     } else {
        if(block.size / distance < precision) {
           force += (dStarMass * (1. / distance)) * (-(G * block.mass) / (distance * distance));
           star.density += block.nbStars / (distance / LIGHT_YEAR);
        } else {
            auto & blocks = std::get<1>(block.contain);
            for(auto i{0}; i < 8; i++)
                if(blocks[i].nbStars > 0)
                    force += forceDensityCalculations(blocks[i], star, precision);
        }
    }

    return force;
}
