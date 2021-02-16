#ifndef RAYCASTER
#define RAYCASTER

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "../common_src/SDLWrappers/SdlContexto.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "Player.h"
#include "Map/WorldMap.h"

class RayCaster {
SdlTexture& walls;

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

void dibujarPisoYTecho(SdlRenderer& renderer, ClientSettings& settings);

public:
  double zBuffer[1024];
  explicit RayCaster(SdlTexture& walls, ClientSettings& settings);
  ~RayCaster();

  void cast3D(SdlRenderer& renderer, WorldMap& myMap, Player& player,
    ClientSettings& settings);
};
#endif
