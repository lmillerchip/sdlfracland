//-----------------------------------------------------------------------------
#include "Scalar.h"
#include <math.h>

//-----------------------------------------------------------------------------
// Constructor
Scalar::Scalar(const double nx, const double ny, const double nz)
{
  x=nx; y=ny; z=nz;
}

//-----------------------------------------------------------------------------
// Copy Constructor
Scalar::Scalar(const Scalar& that)
{
  *this=that;
}

//-----------------------------------------------------------------------------
Scalar&
Scalar::operator=(const Scalar& that)
{
  x = that.x;
  y = that.y;
  z = that.z;
  return(*this);
}

//-----------------------------------------------------------------------------
void
Scalar::operator+=(const Scalar& one)
{
  x+=one.x;
  y+=one.y;
  z+=one.z;
}

//-----------------------------------------------------------------------------
void
Scalar::operator-=(const Scalar& one)
{
  x-=one.x;
  y-=one.y;
  z-=one.z;
}

//-----------------------------------------------------------------------------
Scalar
operator+(const Scalar& one, const Scalar& two)
{
  Scalar res;
  res.x = one.x + two.x;
  res.y = one.y + two.y;
  res.z = one.z + two.z;
  return(res);
}

//-----------------------------------------------------------------------------
Scalar
operator-(const Scalar& one, const Scalar& two)
{
  Scalar res;
  res.x = one.x - two.x;
  res.y = one.y - two.y;
  res.z = one.z - two.z;
  return(res);
}

//-----------------------------------------------------------------------------
double
Scalar::length() const
{
  return(sqrt(x*x+y*y+z*z));
}

//-----------------------------------------------------------------------------
Scalar
Scalar::timesby(const double factor) const
{
  Scalar res;
  res.x = x*factor;
  res.y = y*factor;
  res.z = z*factor;
  return(res);
}

//-----------------------------------------------------------------------------
Scalar
Scalar::cross(const Scalar &b) const
{
  Scalar res;
  res.x = (y * b.z) - (z * b.y);
  res.y = (z * b.x) - (x * b.z);
  res.z = (x * b.y) - (y * b.x);
  return(res);
}

//-----------------------------------------------------------------------------
void
Scalar::makeunit()
{
  double l=length();
  if (l!=0.0) {
    x=x/l;
    y=y/l;
    z=z/l;
  }
}

//-----------------------------------------------------------------------------
double
Scalar::dot(const Scalar& that) const
{
  return((x * that.x) +
         (y * that.y) +
         (z * that.z));
}

//-----------------------------------------------------------------------------
ostream&
operator<<(ostream& strm, const Scalar& s)
{
  return(strm << "(" << s.x << ", " << s.y << ", " << s.z << ") len=" << s.length());
}

//-----------------------------------------------------------------------------
ostream&
operator<<(ostream& strm, const Vector& v)
{
  return(strm << v.position << v.direction);
}

//-----------------------------------------------------------------------------
//                              VECTORS
//-----------------------------------------------------------------------------
Vector&
Vector::operator=(const Vector& that)
{
  position = that.position;
  direction = that.direction;
  return(*this);
}

//-----------------------------------------------------------------------------
// Copy constructor
Vector::Vector(const Vector& that)
{
  *this=that;
}

