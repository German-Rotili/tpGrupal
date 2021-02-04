#ifndef RAYCASTER
#define RAYCASTER

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "Map/WorldMap.h"

class RayCaster {

const int MAX_DEPTH = 30;
const int TEXTURES_HEIGHT = 64;
const double M_PI_180 = M_PI/180;
const double DIRECTION_PER_RAY;
const int HALF_SCREEN_HEIGHT;
const double HALF_FOV;
const double TEXTURE_RELATIVE_HSCALE;

double xStep, yStep;
int tileStepX, tileStepY;

void setTileSteps(double direction);
void setXYSteps(double direction);

public:
  explicit RayCaster(ClientSettings& settings);
  ~RayCaster();

  void cast2D(SdlRenderer& renderer, WorldMap& myMap, double x, double y,
     double actorAngle, ClientSettings& settings);

  void cast3D(SdlRenderer& renderer, WorldMap& myMap, double x, double y,
    double actorAngle, SdlTexture& walls, double zBuffer[],
     ClientSettings& settings);
};
#endif
