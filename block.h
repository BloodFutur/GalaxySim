#ifndef BLOCK_H
#define BLOCK_H

#include "star.h"
#include "vector.h"

//TODO Comment this class

// Area (block) of Barnes-Hut algorithm
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

    void set_size(const double & size);             // Update block size
    void divide(Star::range stars);                       // Divide a block into an octree
    void updateMass(const Star::range & galaxy);    //

    std::variant<Star::list::iterator, std::vector<Block>> contain;
};

void createBlocks(const double & area, Block & block, Star::range & galaxy); // Create blocks
bool isIn(const Block & block, const Star & star);                           // Check if the star is in the block

#endif // BLOCK_H
