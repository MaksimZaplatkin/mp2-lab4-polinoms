#include "monom.h"
#include <vector>
#include <stdexcept>

using namespace std;

double Monom::getCoef() const
{
    return coef;
}
int Monom::getDegrees() const
{
    return deg;
}

void Monom::setCoef(double coeff)
{
    coef = coeff;
}

void Monom::setDegrees(int degr)
{
    deg = degr;
}

int Monom::getXDegree() const
{
    return deg / 100;
}

int Monom::getYDegree() const
{
    return (deg / 10) % 10;
}

int Monom::getZDegree() const
{
    return deg % 10;
}

void Monom::setXDegree(int x)
{
    deg = x * 100 + getYDegree() * 10 + getZDegree();
}

void Monom::setYDegree(int y)
{
    deg = getXDegree() * 100 + y * 10 + getZDegree();
}

void Monom::setZDegree(int z)
{
    deg = getXDegree() * 100 + getYDegree() * 10 + z;
}

Monom Monom::operator +(const Monom& other) const
{
    if (deg != other.deg)
    {
        throw invalid_argument("razniy stepen");
    }
    return Monom(coef + other.coef, deg);
}

Monom Monom::operator * (double scalar) const
{
    return Monom(coef * scalar, deg);
}

Monom Monom::operator*(const Monom& other) const
{
    int x = getXDegree() + other.getXDegree();
    int y = getYDegree() + other.getYDegree();
    int z = getZDegree() + other.getZDegree();
    if (x > 9 || y > 9 || z > 9)
    {
        throw overflow_error("stepen sliskom bolshay pri umnoz");
    }
    return Monom(coef * other.coef, x * 100 + y * 10 + z);
}

bool Monom::operator<(const Monom& other) const
{
    return(deg > other.deg);
}

bool Monom::operator==(const Monom& other) const
{
    return(deg == other.deg);
}

bool Monom::operator!=(const Monom& other) const
{
    return!(*this == other);
}

bool Monom::isZero() const
{
    return (abs(coef) < 1e-6);
}