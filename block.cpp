#include "block.h"
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
    const std::array<std::function<bool(const Star & star)>, 3> testStarAxis =
    {
        [&pivot](const Star& star) {return star.position.x() < pivot.x(); },
        [&pivot](const Star& star) {return star.position.y() < pivot.y(); },
        [&pivot](const Star& star) {return star.position.z() < pivot.z(); }
    };

    std::array<Star::range, 8> result;
    std::size_t iPart {0};
    auto itX = std::partition(stars.begin, stars.end, testStarAxis[0]);
    auto xParts = std::array{ Star::range{stars.begin, itX}, Star::range{itX, stars.end} };

    for (auto & part : xParts)
    {
        auto itY = std::partition(part.begin, part.end, testStarAxis[1]);
        auto yParts = std::array{ Star::range{part.begin, itY}, Star::range{itY, part.end} };

        for (auto & part : yParts)
        {
            auto itZ = std::partition(part.begin, part.end, testStarAxis[2]);
            result[iPart++] = Star::range{ part.begin, itZ };
            result[iPart++] = Star::range{ itZ, part.end };
        }
    }

    return result;
}

/*
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
*/
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
/*
void Block::divide(Star::range stars)
{

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
            //blocks[iBlock].divide(octree[iBlock]);

            if(blocks[iBlock].nbStars > 0) {
                newMass += blocks[iBlock].mass;
                newMassCenter += blocks[iBlock].massCenter * blocks[iBlock].mass;
            }
        }

        mass = newMass;
        massCenter = newMassCenter / newMass;
    }
}

*/
void Block::divide(Star::range stars)
{
    if (stars.begin == stars.end) // pas d'etoile
    {
        contain = stars.begin; // pas très utile, permet de clear la memoire de array<Block, 8> si c'était sa valeur précédente
        nbStars = 0;
        mass = 0.;
        massCenter = Vector(0., 0., 0.);
        asChildren = false;
    }

    else if (std::next(stars.begin) == stars.end) // une étoile
    {
        contain = stars.begin;
        nbStars = 1;
        mass = stars.begin->mass;
        massCenter = stars.begin->position;
        asChildren = false;
    }

    else
    {
        if (contain.index() != 1)
            contain = std::vector<Block>(8);

        nbStars = std::distance(stars.begin, stars.end);
        asChildren = true;

        Block block;

        block.asParents = true;
        block.set_size(size / 2.);

        Vector posis[] =
        {
            {position.x() - size / 4., position.y() - size / 4., position.z() - size / 4.},
            {position.x() - size / 4., position.y() - size / 4., position.z() + size / 4.},
            {position.x() - size / 4., position.y() + size / 4., position.z() - size / 4.},
            {position.x() - size / 4., position.y() + size / 4., position.z() + size / 4.},
            {position.x() + size / 4., position.y() - size / 4., position.z() - size / 4.},
            {position.x() + size / 4., position.y() - size / 4., position.z() + size / 4.},
            {position.x() + size / 4., position.y() + size / 4., position.z() - size / 4.},
            {position.x() + size / 4., position.y() + size / 4., position.z() + size / 4.}
        };

        auto& myblocks = std::get<1>(contain);
        auto partitions_stars = setOctree(stars, position);
        double new_mass = 0.;
        Vector new_mass_center = Vector(0., 0., 0.);
        int i_add = 0;

        for (int ibloc = 0; ibloc < 8; ibloc++)
        {
            myblocks[ibloc] = block;
            myblocks[ibloc].position = posis[ibloc];
            myblocks[ibloc].divide(partitions_stars[ibloc]);

            if (myblocks[ibloc].nbStars > 0)
            {
                new_mass += myblocks[ibloc].mass;
                new_mass_center += myblocks[ibloc].massCenter * myblocks[ibloc].mass;
                i_add++;
            }
        }

        mass = new_mass;
        massCenter = new_mass_center / new_mass;
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
    double hsblock = block.size * 0.5;
    return (p.x() + hsblock > star.position.x() && p.x() - hsblock < star.position.x() &&
            p.y() + hsblock > star.position.y() && p.y() - hsblock < star.position.y() &&
            p.z() + hsblock > star.position.z() && p.z() - hsblock < star.position.z());
}
