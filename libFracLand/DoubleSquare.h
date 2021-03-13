//-----------------------------------------------------------------------------
// FloatSquare object
// This is a square array of doubles
//-----------------------------------------------------------------------------

#ifndef _DOUBLE_SQUARE_H
#define _DOUBLE_SQUARE_H 1

//-----------------------------------------------------------------------------
class DoubleSquare
{
  public:
             // Constructor parameter is size of square's edge
             DoubleSquare(int);
             ~DoubleSquare();

    // Get the size of the square
    int      getSize()
             { return(size); }

    // Get an element
    double   get(int x, int y)
             { return(array[(y*size) + x]); }

    // Set an element
    void     set(int x, int y, double d)
             { array[(y*size) + x] = d; }

    // Set all elements to zero
    void     zero();

  private:
    int      size;
    double*  array;
};

#endif

