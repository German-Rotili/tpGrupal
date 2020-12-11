#ifndef SDLCONTEXTO_H
#define SDLCONTEXTO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SdlException.h"

class SdlContexto {
  public:
    SdlContexto(){
    // Inicializo SDL
      if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        char* error;
        sprintf(error, "SDL Falló init. SDL_Error: %s\n", SDL_GetError());
        throw SdlException(error);
      }
      // Inicializo carga de PNGs
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags)) {
        char* error;
        sprintf(error, "SDL_image error: %s\n", IMG_GetError());
        throw SdlException(error);
      }

    }
    ~SdlContexto(){
      IMG_Quit();
      SDL_Quit();
    }
};

#endif  // SDLCONTEXTO_H
