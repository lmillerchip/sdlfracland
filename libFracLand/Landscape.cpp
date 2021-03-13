//-----------------------------------------------------------------------------
// Landscape object
// This is the core landscape object that represents the height field
// as a square of doubles
//-----------------------------------------------------------------------------

#include "Landscape.h"
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Constructor
Landscape::Landscape(uint32_t s)
{
  if ((s % 2) == 0) ++s;  // Landscape size must be an odd number for the zoom algorithm

  size = s;
  land = new DoubleSquare(s);
  land->zero();
}

//-----------------------------------------------------------------------------
// Destructor
Landscape::~Landscape()
{
  delete land;
}

//-----------------------------------------------------------------------------
bool
Landscape::zero(uint32_t x, uint32_t y)
{
  // Bounds check
  if ((x >= size) || (y >= size)) return(false);
  land->set(x, y, 0.0);
  return(true);
}

//-----------------------------------------------------------------------------
bool
Landscape::zoom(uint32_t x, uint32_t y)
{
  // Bounds check
  if ((x >= size/2) || (y >= size/2)) return(false);

  DoubleSquare* oldLand = land;
  land = new DoubleSquare(size);

  // Copy over relevant parts - this does the zoom but leaves gaps
  uint32_t tmpx;
  uint32_t tmpy;
  for(tmpx = 0; tmpx <= size/2; tmpx++)
  {
    for(tmpy = 0; tmpy <= size/2; tmpy++)
    {
      land->set(tmpx*2, tmpy*2, oldLand->get(x+tmpx, y+tmpy) * 2.0);
    }
  }
  delete oldLand;

  // Fill in the horizontal gaps
  double midHeight;
  double edge = (size - 2);
  for(tmpx = 1; tmpx < size; tmpx += 2)
  {
    for(tmpy = 0; tmpy < size; tmpy += 2)
    {
      if ((tmpx == 1) || (tmpx >= edge))
      {
        midHeight = linearInterpolate(land->get(tmpx-1, tmpy), land->get(tmpx+1, tmpy));
      }
      else
      {
        midHeight = cubicInterpolate(land->get(tmpx-3, tmpy),
                                     land->get(tmpx-1, tmpy),
                                     land->get(tmpx+1, tmpy),
                                     land->get(tmpx+3, tmpy));
      }
      land->set(tmpx, tmpy, midHeight + randomness());
    }
  }

  // Fill in the vertical gaps
  for(tmpx = 0; tmpx < size; tmpx += 2)
  {
    for(tmpy = 1; tmpy < size; tmpy += 2)
    {
      if ((tmpy == 1) || (tmpy >= edge))
      {
        midHeight = linearInterpolate(land->get(tmpx, tmpy-1), land->get(tmpx, tmpy+1));
      }
      else
      {
        midHeight = cubicInterpolate(land->get(tmpx, tmpy-3),
                                     land->get(tmpx, tmpy-1),
                                     land->get(tmpx, tmpy+1),
                                     land->get(tmpx, tmpy+3));
      }
      land->set(tmpx, tmpy, midHeight + randomness());
    }
  }

  // Fill in the central gaps
  for(tmpx = 1; tmpx < size; tmpx += 2)
  {
    for(tmpy = 1; tmpy < size; tmpy += 2)
    {
      midHeight = (land->get(tmpx+1, tmpy)
                 + land->get(tmpx-1, tmpy)
                 + land->get(tmpx, tmpy+1)
                 + land->get(tmpx, tmpy-1)
                  ) / 4.0;
      land->set(tmpx, tmpy, midHeight + randomness());
    }
  }

  return(true);
}

//-----------------------------------------------------------------------------
void
Landscape::dynamicRelax()
{
  DoubleSquare* tmpland = new DoubleSquare(size);

  int i;
  for(i=0; i < 10; i++)
  {
    dynamicRelax(land, tmpland);
    dynamicRelax(tmpland, land);
  }

  delete tmpland;
}

//-----------------------------------------------------------------------------
void
Landscape::dynamicRelax(DoubleSquare* landFrom, DoubleSquare* landTo)
{
  uint32_t x;
  uint32_t y;
  double avg;
  double oldVal;
  double diff;

  for(x=0; x < size; x++)
  {
    for(y=0; y < size; y++)
    {
      if ((x==0) || (y==0) || (x == (size-1)) || (y == (size-1)))
      {
        // Just copy edge pieces - arguably wrong but simpler
        landTo->set(x, y, landFrom->get(x, y));
      } else
      {
        avg  = landFrom->get(x, y+1);
        avg += landFrom->get(x, y-1);
        avg += landFrom->get(x+1, y);
        avg += landFrom->get(x-1, y);
        oldVal = landFrom->get(x, y);
        diff = (avg / 4.0) - oldVal;
        landTo->set(x, y, oldVal + (diff / 4));
      }
    }
  }
}

//-----------------------------------------------------------------------------
// Returns a random double between 1.0 and -1.0
double
Landscape::randomness()
{
  double rv = ((double)rand()) / (double)(RAND_MAX);
  if ((rand() % 2) == 0) rv = -rv;
  return(rv);
}

//-----------------------------------------------------------------------------
double
Landscape::cubicInterpolate(double v0, double v1, double v2, double v3)
{
	double p = (v3 - v2) - (v0 - v1);
	double q = (v0 - v1) - p;
	double r = v2 - v0;

	return((p * 0.5 * 0.5 * 0.5) + (q * 0.5 * 0.5) + (r * 0.5) + v1);
}

