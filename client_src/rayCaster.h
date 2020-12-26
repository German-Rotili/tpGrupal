#ifndef RAYCASTER
#define RAYCASTER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "ClientSettings.h"



class RayCaster {

public:
  void cast2D(SdlRenderer& renderer, double x, double y,
     double dirAngle, ClientSettings& settings);

  void cast3D(SdlRenderer& renderer, double x, double y,
    double dirAngle, SdlTexture& walls, double zBuffer[],
     ClientSettings& settings);
};
#endif
