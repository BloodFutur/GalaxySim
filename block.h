#ifndef BLOCK_H
#define BLOCK_H

#include "star.h"
#include "vector.h"


/** @class Block
 * @brief A block of Barnes-Hut algorithm
 * @note There are many stars, it is impossible to compute all the calculations
 * We compute forces, speed and other properties on average on a block
 * It divides the numbers of computations
 */
class Block
{
public:
    Block() = default;

    Vector position {0,0,0};        // Position of the block
    double mass {0};            // The mass of the block (average of the mass of all stars)
    Vector massCenter {0,0,0};      // Its mass center is the average of stars mass centers
    size_t nbStars{0};         // It is the number of stars in the block

    bool asStars{false};
    bool asChildren{false};
    bool asParents{false};
    int parent{false};

    double size{0.};

    void operator=(const Block& block);

    /**
     * @brief Update block size
     * @param size
     */
    void set_size(const double & size);

    /**
     * @brief Divide a block into octrees
     * @param stars All stars in a block
     */
    void divide(Star::range stars);

    /**
     * @brief Update the mass of a block
     * @param galaxy
     */
    void updateMass(const Star::range & galaxy);

    // Container defined by the union of an iterator and an octree
    // It is to use less memory when manipulating stars
    std::variant<Star::list::iterator, std::vector<Block>> contain;
};

/**
 * @brief Create blocks
 * @param area area of a block
 * @param block The block that will be divided
 * @param galaxy All stars in the galaxy
 */
void createBlocks(const double & area, Block & block, Star::range & galaxy);

/**
 * @brief Check if a Star is in a Block
 * @param block The block where the star can be
 * @param star The star which we will check if it is in the block
 * @return 'true' if the star is in the block, else returns 'false'
 */
bool isIn(const Block & block, const Star & star);

#endif // BLOCK_H
