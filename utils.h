#ifndef UTILS_H
#define UTILS_H

#include <random>

/**
 * @brief Calculate exponents
 * @tparam the base of the exponent
 * @param the exponent number
 * @return return the value of the exponent
 */
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


constexpr double PI         = 3.14159265;
constexpr double G          = (6.674 * E<double>(10,-11));  // Gravitational Constant in ISU
constexpr double LIGHT_YEAR = (9.461 * E<double>(10,15));   // A light year in meters
constexpr double SOLAR_MASS = (1.989 * E<double>(10,30));   // The solar mass in kilograms
constexpr double YEAR       = 31536000.;                    // Year in seconds

/**
 * @brief Return a random double in the interval
 * @param[in] min The lower bound of the interval
 * @param[in] max The upper bound of the interval
 * @returns the random number
 */
double random(const double & min, const double & max);

/**
 * @brief Return a random integer in the interval
 * @param[in] min The lower bound of the interval
 * @param[in] max The upper bound of the interval
 * @returns the random number
 */
int random(const int & min, const int & max);

/**
 * @enum Views
 * @brief The Views enum
 * @details All available views that can be used in the viewport
 */
enum Views { DEFAULT = 0, XY, YZ, ZX};


#endif // UTILS_H
