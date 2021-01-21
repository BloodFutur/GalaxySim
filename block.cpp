#include "block.h"
#include <QDebug>
/*
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
*/
std::array<Star::range, 8> setOctree(Star::range stars, Vector pivot)
{
    std::array<std::function<bool(const Star & star)>, 3> testStarAxis =
    {
        [pivot](const Star& star) {return star.position.x() < pivot.x(); },
        [pivot](const Star& star) {return star.position.y() < pivot.y(); },
        [pivot](const Star& star) {return star.position.z() < pivot.z(); }
    };

    std::array<Star::range, 8> result;
    int iPart = 0;
    Star::list::iterator itX = std::partition(stars.begin, stars.end, testStarAxis[0]);
    auto xParts = std::array{ Star::range{stars.begin, itX}, Star::range{itX, stars.end} };

    for (auto& part : xParts)
    {
        Star::list::iterator itY = std::partition(part.begin, part.end, testStarAxis[1]);
        auto yParts = std::array{ Star::range{part.begin, itY}, Star::range{itY, part.end} };

        for (auto& part : yParts)
        {
            Star::list::iterator itZ = std::partition(part.begin, part.end, testStarAxis[2]);
            result[iPart++] = Star::range{ part.begin, itZ };
            result[iPart++] = Star::range{ itZ, part.end };
        }
    }

    return result;
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

void Block::divide(Star::range stars)
{

    qDebug() << "divide\n";
    // TODO Fill this function
    // No stars case
    // If only one star its trivial
    // else
    // Create a vector of 8 blocks
    // Create an octree
    // for each block we divide it again

    if(stars.begin == stars.end) {
        contain = stars.begin;
        nbStars = 0;
        mass = 0;
        massCenter = Vector(0., 0., 0.);
        asChildren = false;
    } else if(std::next(stars.begin) == stars.end) {
        contain = stars.begin;
        nbStars = 1;
        mass = stars.begin->mass;
        massCenter = stars.begin->position;
        asChildren = false;
    } else {
        if(contain.index() != 1)
            contain = std::vector<Block>(8);

        nbStars = std::distance(stars.begin, stars.end);
        qDebug() << nbStars;
        asChildren = true;

        Block block;
        block.asParents = true;
        block.set_size(size / 2);

        double qSize = size / 4.;

        Vector pos[] {
            {position.x() - qSize, position.y() - qSize, position.z() - qSize},
            {position.x() - qSize, position.y() + qSize, position.z() - qSize},
            {position.x() - qSize, position.y() - qSize, position.z() + qSize},
            {position.x() - qSize, position.y() + qSize, position.z() + qSize},
            {position.x() + qSize, position.y() - qSize, position.z() - qSize},
            {position.x() + qSize, position.y() + qSize, position.z() - qSize},
            {position.x() + qSize, position.y() - qSize, position.z() + qSize},
            {position.x() + qSize, position.y() + qSize, position.z() + qSize},
        };

        auto& blocks = std::get<1>(contain);

        auto octree = setOctree(stars, position);
        double newMass = 0.;
        Vector newMassCenter = Vector(0., 0., 0.);

        for(auto iBlock{0}; iBlock < 8; iBlock++) {
            blocks[iBlock] = block;
            blocks[iBlock].position = pos[iBlock];
            blocks[iBlock].divide(octree[iBlock]);

            if(blocks[iBlock].nbStars > 0) {
                newMass += blocks[iBlock].mass;
                newMassCenter += blocks[iBlock].massCenter * blocks[iBlock].mass;
            }
        }

        mass = newMass;
        massCenter = newMassCenter;
    }
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
