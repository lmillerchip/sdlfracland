//-----------------------------------------------------------------------------
// Landscape object for SDL2
//-----------------------------------------------------------------------------

#ifndef INCL_LANDSCAPESDL_H
#define INCL_LANDSCAPESDL_H 1

#include <stdint.h>
#include <SDL2/SDL.h>
#include "libFracLand/Landscape.h"
#include "libFracLand/Scalar.h"

//-----------------------------------------------------------------------------
class LandscapeSDL
{
  public:
                   LandscapeSDL(uint32_t);
                   ~LandscapeSDL();

    // Event handlers
    void           handleMouseClick(int button, int x, int y);
    
    // Get the current size
    int            getSize() { return(size); }

    // Create the initial texture
    bool           createTexture();

    // Render the current texture
    void           render();

    // Update the texture to reflect the current state
    void           updateTexture();

    // Variables
    SDL_Window*    screen;
    SDL_Renderer*  renderer;

  private:
    void           getColour(uint32_t x, uint32_t y, uint8_t& r, uint8_t& g, uint8_t& b);

    // Variables
    Landscape      land;
    uint32_t       size;
    Scalar         toLightSource;
    SDL_Texture*   texture;
};

#endif


