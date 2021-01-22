#ifndef STAR_H
#define STAR_H

#include "vector.h"
#include <GLES3/gl3.h>
#include <QOpenGLFunctions>
class Block;



/** @class Star
 * @brief This class defiens a star in a galaxy
 */
class Star
{
public:
    // array of Stars
    using list = std::vector<Star>; // The name list is not very well

    /** @struct range
     * @brief range of a std::vector<Star>
     */
    struct range {
        list::iterator begin;
        list::iterator end;
    };

    ///
    /// Constructors
    ///
    Star() = default;
    virtual ~Star() = default;

    /**
     * @brief Create a Star with some parameters
     * @param speedInit Initial speed of the star
     * @param area Area of the galaxy where the star will be randomly created
     * @param step The step of time between two position
     * @param galaxyThickness The thickness of the galaxy
     */
    Star(const double & speedInit, const double & area, const double & step, const double & galaxyThickness);
    Star(const Star & star) = default;

    ///
    /// Members
    ///
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

    ///
    /// Updates
    ///

    /**
     * @brief Update the position of the star
     * @param step The step of time between two positions
     * @param verletIntegration Wether use the Verlet integration
     */
    void updatePosition(const double & step, bool verletIntegration);

    /**
     * @brief Update the speed of the star
     * @param step The step of time between two positions
     * @param area The visible area of the galaxy
     */
    void updateSpeed(const double & step, const double & area);

    /**
     * @brief Update the acceleration and the density of the star
     * @param block A block in Barnes-Hut algorithm (it is an area)
     * @param precision Precision of calculations
     */
    void updateAccelerationDensity(const Block & block, const double & precision);

    /**
     * @brief Update the color of the star
     * @details Update thte color of the star according to its density
     */
    void updateColor(); // Compared to the density

    void operator=(const Star & star);
};

/**
 * @brief Initialize a galaxy
 * @param galaxy Container with all stars that will be in the galaxy
 * @param starsNumber The number of stars in the galaxy
 * @param area The area of the galaxy
 * @param speedInit The initial speed of stars
 * @param step The step of time between two positions
 * @param isBlackHole Simulation with or without a black hole (useless)
 * @param blackHoleMass The mass of the black hole in kg
 * @param galaxyThickness The thickness of the galaxy
 * @details Initalize a galaxy with the parameters given
 * Create proportion of stars with higer mass than the other
 */
void initializeGalaxy(Star::list & galaxy, const int & starsNumber, const double & area,
                      const double & speedInit, const double & step,
                      bool isBlackHole, const double & blackHoleMass,
                      const double & galaxyThickness);

/**
 * @brief Compute forces applied on a star and update its density
 * @param block A block in the Barnes-Hut algorithm
 * @param star The star which we will computes forces and density
 * @param precision The precision of computations
 * @return the average force applied on the star
 */
Vector forceDensityCalculations(const Block& block, Star & star, const double & precision);

#endif // STAR_H
