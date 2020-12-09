#ifndef RAYCASTER
#define RAYCASTER

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"

class RayCaster {

public:
  void cast2D(SdlRenderer *renderer, double dirAngle, int actorX, int actorY, double actorDX, double actorDY, double FOV);

  void cast3D(SdlRenderer *renderer, double dirAngle, int actorX, int actorY, double actorDX, double actorDY, double FOV);
};
#endif
