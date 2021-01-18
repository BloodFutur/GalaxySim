#include "utils.h"


double random(const double &min, const double &max)
{
    return (double(rand()) / double(RAND_MAX) * (max - min) + min);

}

int random(const int &min, const int &max)
{
    return (rand() % (max - min) + min);
}
