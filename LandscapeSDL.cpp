//-----------------------------------------------------------------------------
// Landscape object for SDL2
//-----------------------------------------------------------------------------

#include "LandscapeSDL.h"

//-----------------------------------------------------------------------------
// Constructor
LandscapeSDL::LandscapeSDL(uint32_t sz):
  screen{nullptr},
  renderer{nullptr},
  land{sz},
  size{sz},
  texture{nullptr}
{
  toLightSource.set(0.1f, -0.2f, 1.0f);
  toLightSource.makeunit();
}

//-----------------------------------------------------------------------------
// Destructor
LandscapeSDL::~LandscapeSDL()
{
  if (renderer) SDL_DestroyRenderer(renderer);
  if (screen)   SDL_DestroyWindow(screen);
}

//-----------------------------------------------------------------------------
bool
LandscapeSDL::createTexture()
{
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size, size);
  if (texture == nullptr)
  {
    fprintf(stderr, "Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
    return(false);
  }

  return(true);
}

//-----------------------------------------------------------------------------
void
LandscapeSDL::updateTexture()
{
  uint32_t x;
  uint32_t y;
  uint8_t r;
  uint8_t g;
  uint8_t b;

  // Render to the texture
  SDL_SetRenderTarget(renderer, texture);

  for(y=0; y < size; y++)
  {
    for(x=0; x < size; x++)
    {
      getColour(x, y, r, g, b);
      SDL_SetRenderDrawColor(renderer, r, g, b, 0xff);
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }

  // Reset the render target
  SDL_SetRenderTarget(renderer, nullptr);
}

//-----------------------------------------------------------------------------
void
LandscapeSDL::handleMouseClick(int button, int x, int y)
{
  if (button == 2)
  {
    //land.zero(x, y);
    land.zero(x+1, y);
    land.zero(x-1, y);
    land.zero(x, y+1);
    land.zero(x, y-1);
    updateTexture();
    return;
  }

  if (button == 3)
  {
    land.dynamicRelax();
    updateTexture();
    return;
  }
  
  // The user clicks on the centre of the zoom-in box, but the zoom
  // routine wants the top-left corner, so work out where it is
  int zoomx = x - (size/4);
  int zoomy = y - (size/4);

  // Force the zoom box completely onto the landscape
  if (zoomx < 0) zoomx = 0;
  if (zoomy < 0) zoomy = 0;
  if (zoomx >= static_cast<int>(size/2)) zoomx = (size/2) - 1;
  if (zoomy >= static_cast<int>(size/2)) zoomy = (size/2) - 1;

  // Do the zoom
  //printf("Zoom event (%d, %d)\n", zoomx, zoomy);
  if (land.zoom(zoomx, zoomy))
  {
    updateTexture();
  } else
  {
    fprintf(stderr, "Invalid zoom at (%d, %d)\n", zoomx, zoomy);
  }
}

//-----------------------------------------------------------------------------
void
LandscapeSDL::getColour(uint32_t x, uint32_t y, uint8_t& r, uint8_t& g, uint8_t& b)
{
  // Check for underwater
  double here = land.height(x, y);
  if (here <= 0.0)
  {
    // Water
    r = 0;
    g = 0;
    b = 192;
    return;
  }

  // Land
  r = 0;
  g = 128;
  b = 64;
  
  // Fake it if we're rammed up against the edge
  if ((x >= size-1) || (y >= size-1)) return;

  Scalar    upVector(0.0, 1.0, land.height(x, y+1) - here);
  Scalar rightVector(1.0, 0.0, land.height(x+1, y) - here);
  Scalar normalVector(rightVector.cross(upVector));
  normalVector.makeunit();
  
  double incidentLight = normalVector.dot(toLightSource);
  if (incidentLight > 0.0)
  {
    r = (unsigned char)(incidentLight * 255.0);
    g += (unsigned char)(incidentLight * 128.0);
  }
  if (incidentLight < 0.0) g -= (unsigned char)((incidentLight + 1.0) * 128.0);
}

//-----------------------------------------------------------------------------
void
LandscapeSDL::render()
{
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = size;
  rect.h = size;

  SDL_RenderCopy(renderer, texture, &rect, &rect);
}

