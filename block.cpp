#include "block.h"

std::array<Star::range, 8> setOctree(Star::range stars, Vector center) {
    // for each axis check if position of the star < center pos
    // For each axis
    std::array<Star::range, 8> octree;
    Star::list::iterator itX = std::partition(stars.begin, stars.end,
                                              [center](const Star & star) {
        return star.position.x() < center.x();
    });
    auto xBlocks = std::array {
            Star::range {stars.begin, itX},
            Star::range {itX, stars.end}
    };

    int part {0};
    for(auto & xBlock : xBlocks) {
        Star::list::iterator itY = std::partition(xBlock.begin, xBlock.end,
                                                  [center](const Star & star) {
            return star.position.y() < center.y();
        });
        auto yBlocks = std::array {
                Star::range {stars.begin, itY},
                Star::range {itY, stars.end}
        };

        for(auto & block : yBlocks) {
            Star::list::iterator itZ = std::partition(block.begin, block.end,
                                                      [center](const Star & star) {
                return star.position.z() < center.z();
            });
            octree[part++] = Star::range{ block.begin, itZ};
            octree[part++] = Star::range{ itZ, block.end};
        }
    }
    return octree;
}

Block::Block()
{
    position = Vector(0. ,0. ,0.);
    mass = 0.;
    massCenter = Vector(0., 0., 0.);
    nbStars = 0;
    asStars = false;
    asChildren = false;
    asParents = false;
    size = 0.;
}

Block::Block(const Block &block)
{
    position = Vector(0. ,0. ,0.);
    mass = 0.;
    massCenter = Vector(0., 0., 0.);
    nbStars = 0;
    asStars = false;
    asChildren = false;
    asParents = false;
    size = 0.;
}

void Block::operator=(const Block &block)
{
    position = block.position;
    mass = block.mass;
    massCenter = block.massCenter;
    nbStars = block.nbStars;
    asStars = block.asStars;
    asChildren = block.asChildren;
    asParents = block.asParents;
    size = block.size;
}

void Block::set_size(const double &size)
{
    this->size = size;
}

void Block::divide(Star::range)
{
    // No stars case
    // If only one star its trivial
    // else
    // Create a vector of 8 blocks
    // Create an octree
    // for each block we divide it again
}

void Block::updateMass(const Star::range &galaxy)
{
    mass = 0;
    massCenter = Vector(0., 0., 0.);
    for(auto it = galaxy.begin; it != galaxy.end; it++) {
        massCenter += it->mass * it->position;
        mass += it->mass;
    }

    massCenter = massCenter / mass;

}


void createBlocks(const double &area, Block &block, Star::range &galaxy)
{
    block.set_size(area);
    block.divide(galaxy);
}

bool isIn(const Block &block, const Star &star)
{
    Vector p = block.position;
    double hsblock = block.size / 2;
    return (p.x() + hsblock > p.x() && p.x() - hsblock < p.x() &&
            p.y() + hsblock > p.y() && p.y() - hsblock < p.y() &&
            p.z() + hsblock > p.z() && p.z() - hsblock < p.z());
}
