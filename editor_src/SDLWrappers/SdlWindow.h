#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SdlException.h"
#include "SdlRenderer.h"

class SdlWindow {
  SDL_Window* window;
  public:
    SdlWindow(std::string nombre, int width, int height);
    ~SdlWindow();
    SdlRenderer getRenderer();
};

#endif  // SDLWINDOW_H
