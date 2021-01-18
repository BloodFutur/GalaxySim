#ifndef UTILS_H
#define UTILS_H

#include <random>


template <typename T>
constexpr T E(T x, int y) {
    return[&]() {
        T res {x};
        for(int i = 1; i < y; i++)
            if(y >= 0)
                res *= x;
            else
                res /= x;
        return res;
    }();

}


constexpr double PI = 3.14159265;
constexpr double G = (6.674 * E<double>(10,-11)); // in ISU
constexpr double LIGHT_YEAR = (9.461 * E<double>(10,15)); // A light year in meters
constexpr double SOLAR_MASS = (1.989 * E<double>(10,30)); // The solar mass in kilograms
constexpr double YEAR = 31536000.; // Year in seconds

double random(const double & min, const double & max);
int random(const int & min, const int & max);


#endif // UTILS_H
