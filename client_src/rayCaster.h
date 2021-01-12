#ifndef RAYCASTER
#define RAYCASTER

#include <stdio.h>
#include <iostream>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "ClientSettings.h"

class RayCaster {

const int MAX_DEPTH = 8;

public:
  void cast2D(SdlRenderer& renderer, double x, double y,
     double dirAngle, ClientSettings& settings);

  void cast3D(SdlRenderer& renderer, double x, double y,
    double dirAngle, SdlTexture& walls, double zBuffer[],
     ClientSettings& settings);
};
#endif
