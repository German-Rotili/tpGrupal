#ifndef SDLCONTEXTO_H
#define SDLCONTEXTO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SdlException.h"

class SdlContexto {
  public:
    SdlContexto();
    ~SdlContexto();
};

#endif  // SDLCONTEXTO_H
