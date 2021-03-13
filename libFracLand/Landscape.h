//-----------------------------------------------------------------------------
// Landscape object
// This is the core landscape object that represents the height field
// as a square of doubles
//-----------------------------------------------------------------------------

#ifndef _LANDSCAPE_H
#define _LANDSCAPE_H 1

#include <stdint.h>
#include "DoubleSquare.h"

//-----------------------------------------------------------------------------
class Landscape
{
  public:
                  // Constructor parameter is size of landscape
                  Landscape(uint32_t);
                  ~Landscape();

    // Get the height at a specific point
    double        height(uint32_t x, uint32_t y)
                  { return(land->get(x, y)); }

    // Make the height at a specific point zero
    bool          zero(uint32_t x, uint32_t y);

    // Zoom the landscape in. The given coordinates are the point where
    // the new top left will be, and should be in the range zero to
    // size / 2.
    // Returns true on success, false on failure.
    bool          zoom(uint32_t x, uint32_t y);

    // Dynamically relax the heightfield.
    void          dynamicRelax();

  private:
    void          dynamicRelax(DoubleSquare*, DoubleSquare*);
    double        randomness();
    double        cubicInterpolate(double a, double b, double c, double d);
    double        linearInterpolate(double a, double b) { return((a+b)/2.0); }

    // Variables
    uint32_t      size;
    DoubleSquare* land;
};

#endif
