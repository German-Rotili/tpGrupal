#ifndef SDLCONTEXT_H
#define SDLCONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SdlException.h"
#include <iostream>

class SdlContext {
  public:
    // Inicializa SDL, image, ttf y mixer
    SdlContext();
    // Libera lo inicializado
    ~SdlContext();
};

#endif  // SdlContext_H
