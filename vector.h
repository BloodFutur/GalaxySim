#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <atomic>
#include <variant>

/** @class Vector
 * @brief A mathematical vector
 * @details A mathematical vector
 * Manage spherical and cartesian coordinates systems
 * Manage most of all operators (vectorial and dot product)
 */

class Vector
{
public:

    ///
    /// Constructors
    ///

    /**
     * @brief Default Vector constructor
     */
    Vector();
    /**
     * @brief Create a Vector from 3D coordinates in cartesian system
     * @param x coordinate in the cartesian system
     * @param y coordinate in the cartesian system
     * @param z coordinate in the cartesian system
     */
    Vector(const double &x, const double &y, const double &z);

    /**
     * @brief Create a vector from another Vector
     * @param vector
     */
    Vector(const Vector &vector);

    /**
     * @brief Create a vector from spherical coordinates
     * @details Create a vector from spherical coordinates and
     *  store it in cartesian coordinates system
     * @param radius The radius coordinate
     * @param phi   The phi angle coordinate
     * @param theta The theta angle coordinate
     * @return the vector converted with cartesian coordinates
     */
    static Vector createSpherical(const double &radius,
                                  const double &phi,
                                  const double &theta);

    ///
    /// Getter
    ///

    /// Cartesian coordinates
    /**
     * @brief Get x coordinate
     * @return the x coordinate of the vector
     */
    double x() const noexcept;          // in meters

    /**
     * @brief Get y coordinate
     * @return the y coordinate of the vector
     */
    double y() const noexcept;          // in meters

    /**
     * @brief Get z coordinate
     * @return the z coordinate of the vector
     */
    double z() const noexcept;          // in meters

    /// Spherical coordinates
    /**
     * @brief Get r coordinate
     * @return the r coordinate of the vector
     */
    [[nodiscard]] double getRadius() const noexcept;  // in meters

    /**
     * @brief Get phi angle coordinate
     * @return the phi angle of the vector in radians
     */
    [[nodiscard]] double getPhi() const noexcept;     // in radians

    /**
     * @brief Get theta angle coordinate
     * @return the theta angle of the vector in radians
     */
    [[nodiscard]] double getTheta() const noexcept;   // in radians

    ///
    /// Setters
    ///

    /**
     * @brief Set new x coordinate value
     * @param val new value for x
     */
    void x(const double &val) noexcept;

    /**
     * @brief Set new y coordinate value
     * @param val new value for y
     */
    void y(const double &val) noexcept;

    /**
     * @brief Set new z coordinate value
     * @param val new value for z
     */
    void z(const double &val) noexcept;

    ///
    /// Operators
    ///
    /**
     * @brief Assign this vectors values from another vector
     * @param vector
     */
    void operator=(const Vector& vector) noexcept;

    Vector& operator+=(const Vector& vector) noexcept;
    Vector& operator-=(const Vector& vector) noexcept;
    Vector& operator*=(const double & number) noexcept;
    Vector& operator/=(const double & number);

private:
    double _x; // Coordinate x          (in meters)
    double _y; // Coordinate y          (in meters)
    double _z; // Coordinate z          (in meters)
};

///
/// Projection of spherical coordinates onto cartesian axes
///

/**
 * @brief Projection on x axis of spherical coordinates
 * @param radius
 * @param phi
 * @param theta
 * @return the projection on x axis
 */
double projOnX(const double &radius, const double &phi, const double &theta);

/**
 * @brief Projection on y axis of spherical coordinates
 * @param radius
 * @param phi
 * @param theta
 * @return the projection on y axis
 */
double projOnY(const double &radius, const double &phi, const double &theta);

/**
 * @brief Projection on z axis of spherical coordinates
 * @param radius
 * @param phi
 * @param theta
 * @return the projection on z axis
 */
double projOnZ(const double &radius, const double &phi, const double &theta);

///
/// Operators
///

Vector operator+(Vector  lhs, Vector const & rhs) noexcept;
Vector operator-(Vector  lhs, Vector const & rhs) noexcept;

/**
 * @brief Dot product of two vectors
 * @param lhs
 * @param rhs
 * @return the dot product value
 */
double operator*(Vector  & lhs, Vector const & rhs) noexcept;

/**
 * @brief Vectorial product of two vectors
 * @param lhs
 * @param rhs
 * @return the result of the vectorial product
 */
Vector operator^(Vector  lhs, Vector const & rhs) noexcept;

Vector operator/(Vector  lhs, double const & rhs) noexcept;
Vector operator*(Vector  lhs, double const & rhs) noexcept;
Vector operator*(double const & lhs, Vector  rhs ) noexcept;

bool operator==(Vector & lhs, Vector const & rhs) noexcept;
bool operator!=(Vector & lhs, Vector const & rhs) noexcept;


/**
 * @brief Get the distance between 2 points
 * @param lhs First point
 * @param rhs Second point
 * @return the distance between these 2 points
 */
double getRadius(Vector const & lhs, Vector const & rhs) noexcept;

/**
 * @brief Get the phi angle between 2 points
 * @param lhs First point
 * @param rhs Second point
 * @return the phi angle between 2 points in radians (spherical system)
 */
double getPhi(Vector const & lhs, Vector const & rhs) noexcept;

/**
 * @brief Get the theta angle between 2 points
 * @param lhs First point
 * @param rhs Second point
 * @return the theta angle between 2 ponts in radins (spherical system)
 */
double getTheta(Vector const & lhs, Vector const & rhs) noexcept;

/**
 * @brief Get normalized vector
 * @param vec Vector that will be normalized
 * @return the normalized vector of a vector
 */
Vector normalize(Vector const & vec);

#endif // VECTOR_H
