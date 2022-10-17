#pragma once

#include <ostream>

#include "config.h"
#include "initializer_list"

class Vector
{
public:
    // DO NOT CHANGE THIS
    Vector(const Vector&) = default;
    Vector& operator=(const Vector&) = default;
    ~Vector() = default;
    //

    // Add suitable constructors
    Vector();
    Vector(std::initializer_list<value> pCoordinates);
    // possibly more

// Public Member functions here
    Vector operator+(const Vector& v1);
    Vector& operator+=(const Vector& rhs);
    Vector& operator+=(const value& n);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(const value& n);
    Vector& operator*(const value& n);
    value operator[](const int n) const;
    value& operator[](const int n);
    value operator*(const Vector& rhs);



    // More to go

private:
    // Private Member functions here

    value coordinates[NDIM];

    // Member variables are ALWAYS private, and they go here
};



// Nonmember function operators go here
std::ostream& operator << (std::ostream& os, const Vector& v);