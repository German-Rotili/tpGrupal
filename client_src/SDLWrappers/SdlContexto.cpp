#include "SdlContexto.h"

SdlContexto::SdlContexto() {
// Inicializo SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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
SdlContexto::~SdlContexto() {
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
