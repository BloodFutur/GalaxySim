#include "vector.h"
#include "utils.h"
#include <cassert>


// Use null vector by default
Vector::Vector()
{
    _x = 0;
    _y = 0;
    _z = 0;
}

Vector::Vector(const double &x, const double &y, const double &z)
{
    this->_x = x;
    this->_y = y;
    this->_z = z;

}

Vector::Vector(const Vector &vector)
{
    _x = vector.x();
    _y = vector.y();
    _z = vector.z();

}

Vector Vector::createSpherical(const double &radius, const double &phi, const double &theta)
{
    return Vector(projOnX(radius,phi,theta),
                  projOnY(radius,phi,theta),
                  projOnZ(radius,phi,theta));
}

double Vector::x() const noexcept
{
    return _x;
}

double Vector::y() const noexcept
{
    return _y;
}

double Vector::z() const noexcept
{
    return _z;
}

void Vector::x(const double &val) noexcept
{
    _x = val;
}

void Vector::y(const double &val) noexcept
{
    _y = val;
}

void Vector::z(const double &val) noexcept
{
    _z = val;
}

double Vector::getRadius() const noexcept
{
    return sqrt(_x*_x+_y*_y+_z*_z);
}

double Vector::getPhi() const noexcept
{
    if(_y > 0 )
        return acos(_x / sqrt(_x*_x + _y * _y));
    else
        return 2 * PI - acos(_x / sqrt(_x*_x + _y * _y));
}

double Vector::getTheta() const noexcept
{
    return acos(_z / getRadius());
}

void Vector::operator=(const Vector &vector) noexcept
{
    _x = vector.x();
    _y = vector.y();
    _z = vector.z();
}

Vector& Vector::operator+=(const Vector &vector) noexcept
{
    _x += vector.x();
    _y += vector.y();
    _z += vector.z();
    return *this;
}

Vector& Vector::operator-=(const Vector &vector) noexcept
{
    _x -= vector.x();
    _y -= vector.y();
    _z -= vector.z();
    return *this;
}

Vector &Vector::operator*=(const double &number) noexcept
{
    assert(number == 0 && "You thought you can divide by 0?");
    _x *= number;
    _y *= number;
    _z *= number;
}

Vector &Vector::operator/=(const double &number)
{
    assert(number == 0 && "You thought you can divide by 0?");
    _x /= number;
    _y /= number;
    _z /= number;
}


Vector operator+(Vector lhs, Vector const & rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

Vector operator-(Vector lhs, Vector const & rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}

double operator*(Vector &lhs, const Vector &rhs) noexcept
{
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

Vector operator^(Vector lhs, const Vector &rhs) noexcept
{
    return Vector(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                  lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                  lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

Vector operator/(Vector lhs, const double &rhs) noexcept
{
    lhs /= rhs;
    return lhs;
}

bool operator==(Vector &lhs, const Vector &rhs) noexcept
{
    return (lhs.x() == rhs.x() &&
            lhs.y() == rhs.y() &&
            lhs.z() == rhs.z());
}

bool operator!=(Vector &lhs, const Vector &rhs) noexcept
{
    return !(lhs == rhs);
}

double projOnX(const double &radius, const double &phi, const double &theta)
{
    return radius * cos(phi) * sin(theta);
}

double projOnY(const double &radius, const double &phi, const double &theta)
{
    return radius * sin(phi) * sin(theta);

}

double projOnZ(const double &radius, const double &phi, const double &theta)
{
    return radius * cos(theta);
}

double getRadius(const Vector &lhs, const Vector &rhs) noexcept
{
    return (lhs - rhs).getRadius();
}

double getPhi(const Vector &lhs, const Vector &rhs) noexcept
{
    return (lhs - rhs).getPhi();
}

double getTheta(const Vector &lhs, const Vector &rhs) noexcept
{
    return (lhs - rhs).getTheta();
}

Vector normalize(const Vector &vec)
{
    return vec / vec.getRadius();
}

Vector operator*(Vector lhs, const double &rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

Vector operator*(const double &lhs, Vector rhs) noexcept
{
    rhs *= lhs;
    return rhs;
}
