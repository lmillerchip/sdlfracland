//-----------------------------------------------------------------------------
#ifndef _INCL_SCALAR_H
#define _INCL_SCALAR_H

#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
// This class represents a scalar, i.e. a vector with one end attached to the
// origin.
class Scalar
{
  public:
    // Constructors
                        Scalar() {x=y=z=0.0;}         // Normal constructor
                        Scalar(const double, const double, const double);
                        Scalar(const Scalar&);      // Copy constructor

    // Operators
    Scalar&             operator=(const Scalar&);     // Assignment operator
    void                operator+=(const Scalar&);    // Increment operator
    void                operator-=(const Scalar&);    // Decrement operator
    friend Scalar       operator+(const Scalar&, const Scalar&);
    friend Scalar       operator-(const Scalar&, const Scalar&);
    friend ostream&     operator<<(ostream&, const Scalar&);
    friend Scalar       operator*(const Scalar& s, const double d)
                        { return(s.timesby(d)); }

    double              length() const;
    void                makeunit();
    Scalar              timesby(const double) const;
    void                set(const double nx, const double ny, const double nz)
                        {x=nx; y=ny; z=nz;}

    double              dot(const Scalar&) const;
    Scalar              cross(const Scalar&) const;

    // Variables
    double x, y, z;
};
 
//-----------------------------------------------------------------------------
class Vector
{
  public:
    // Methods
    Vector() {};
    Vector(const Vector&);
    Vector& operator=(const Vector&);
 
    // Variables
    Scalar position, direction;
};
 
//-----------------------------------------------------------------------------
ostream& operator<<(ostream&, const Vector&);

#endif
