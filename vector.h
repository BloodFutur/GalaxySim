#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <atomic>
#include <variant>
#include <list>

class Vector
{
public:
    Vector();
    Vector(const double &x, const double &y, const double &z);
    Vector(const Vector &vector);

    // Create a Vector from Spherical coordinates system
    static Vector createSpherical(const double &radius, const double &phi, const double &theta);

    // Get the coordinates of the vector using cartesian system
    double x() const noexcept;          // in meters
    double y() const noexcept;          // in meters
    double z() const noexcept;          // in meters

    void x(const double &val) noexcept;
    void y(const double &val) noexcept;
    void z(const double &val) noexcept;

    // Get the coordinates of the vector using spherical system
    [[nodiscard]] double getRadius() const noexcept;  // in meters
    [[nodiscard]] double getPhi() const noexcept;     // in radians
    [[nodiscard]] double getTheta() const noexcept;   // in radians

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

// Projection of the spherical vector on cartesian axes
double projOnX(const double &radius, const double &phi, const double &theta);
double projOnY(const double &radius, const double &phi, const double &theta);
double projOnZ(const double &radius, const double &phi, const double &theta);


// Operators

Vector operator+(Vector  lhs, Vector const & rhs) noexcept;
Vector operator-(Vector  lhs, Vector const & rhs) noexcept;

// Dot product
double operator*(Vector  & lhs, Vector const & rhs) noexcept;

// Vectorial product
Vector operator^(Vector  lhs, Vector const & rhs) noexcept;

Vector operator/(Vector  lhs, double const & rhs) noexcept;
Vector operator*(Vector  lhs, double const & rhs) noexcept;
Vector operator*(double const & lhs, Vector  rhs ) noexcept;

bool operator==(Vector & lhs, Vector const & rhs) noexcept;
bool operator!=(Vector & lhs, Vector const & rhs) noexcept;


// Give the distance between 2 points   (in meters)
double getRadius(Vector const & lhs, Vector const & rhs) noexcept;

// Give phi angle between 2 points      (in radians)
double getPhi(Vector const & lhs, Vector const & rhs) noexcept;

// Give theta angle between 2 points    (in radians)
double getTheta(Vector const & lhs, Vector const & rhs) noexcept;

// Give the normalized vector
Vector normalize(Vector const & vec);

#endif // VECTOR_H
