//-----------------------------------------------------------------------------
// DoubleSquare object
//-----------------------------------------------------------------------------

#include "DoubleSquare.h"

//-----------------------------------------------------------------------------
// Constructor
DoubleSquare::DoubleSquare(int s)
{
  size = s;
  array = new double[s*s];
}

//-----------------------------------------------------------------------------
// Destructor
DoubleSquare::~DoubleSquare()
{
  delete [] array;
}

//-----------------------------------------------------------------------------
void
DoubleSquare::zero()
{
  int i;
  int max = size * size;
  for(i=0; i < max; i++)
  {
    array[i] = 0.0;
  }
}
