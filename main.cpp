//-----------------------------------------------------------------------------
// Main routine for SDL fractal landscape
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LandscapeSDL.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define LANDSCAPE_SIZE 512
#else
#define LANDSCAPE_SIZE 1024
#endif

LandscapeSDL land(LANDSCAPE_SIZE);
bool quit = false;

//----------------------------------------------------------------------------
bool
handleEvent(SDL_Event& event, LandscapeSDL& land)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_q) return(false);
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN)
  {
    land.handleMouseClick(event.button.button, event.button.x, event.button.y);
  }
  return(true);
}

//-----------------------------------------------------------------------------
void
animate(LandscapeSDL& land)
{
  // Clear screen
  SDL_SetRenderDrawColor(land.renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(land.renderer);

  land.render();

  // Swap buffers
  SDL_RenderPresent(land.renderer);
}
 
//-----------------------------------------------------------------------------
void
mainLoop(void)
{
  if (quit) return;
  // Main event loop
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      // Quit the program
      quit = true;
    }
    else
    {
      quit = !handleEvent(event, land);
    }
  }

  animate(land);
}

//-----------------------------------------------------------------------------
int
main()
{
  printf("Fractal landscape demo\n");

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    return(1);
  }

  srand(time(nullptr));

  land.screen = SDL_CreateWindow("Fractal Landscape",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      LANDSCAPE_SIZE, LANDSCAPE_SIZE, SDL_WINDOW_SHOWN);

  if (land.screen == nullptr)
  {
    fprintf(stderr, "Screen could not be created: %s\n", SDL_GetError());
    return(1);
  }

  land.renderer = SDL_CreateRenderer(land.screen, -1, SDL_RENDERER_ACCELERATED);
  if (land.renderer == nullptr)
  {
    fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
    return(1);
  }

  if (!land.createTexture()) return(1);

  land.LandscapeSDL::handleMouseClick(1, 0, 0);
  land.LandscapeSDL::handleMouseClick(1, 0, 0);
  land.LandscapeSDL::handleMouseClick(1, 0, 0);
  land.updateTexture();

  printf("Click anywhere to zoom in.\n");
  printf("Zoom is infinite, you can explore as long as you like!\n");
  printf("For best results, zoom in on coastlines.\n");

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(mainLoop, 0, 1);
#else
  while(!quit)
    mainLoop();
#endif
 
  // Tidy up
  SDL_Quit();
  return(0);
}
