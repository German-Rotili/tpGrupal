#ifndef SDLCONTEXTO_H
#define SDLCONTEXTO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "SdlException.h"

class SdlContexto {
  public:
    SdlContexto(){
    // Inicializo SDL
      if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        char error[BUF_SIZE];
        snprintf(error, sizeof(error), "SDL Falló init. SDL_Error: %s\n", SDL_GetError());
        throw SdlException(error);
      }
      // Inicializo carga de PNGs
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags)) {
        char error[BUF_SIZE];
        snprintf(error, sizeof(error), "SDL_image error: %s\n", IMG_GetError());
        throw SdlException(error);
      }
      //Inicializo carga de fuentes
      if (TTF_Init() == -1) {
        char error[BUF_SIZE];
        snprintf(error, sizeof(error), "SDL_ttf Error: %s\n", TTF_GetError());
        throw SdlException(error);
      }

    }
    ~SdlContexto(){
      TTF_Quit();
      IMG_Quit();
      SDL_Quit();
    }
};

#endif  // SDLCONTEXTO_H
