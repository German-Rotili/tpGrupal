#include "rayCaster.h"
#include <stdio.h>
#include <cmath>
#include <utility>
#include <tuple>
#include <vector>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "ClientSettings.h"
#include "Map/WorldMap.h"

std::vector<std::vector<int>> worldMap = {
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
                       {1, 0, 0, 0, 0, 0, 3, 0, 0, 1},
                       {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
                       {1, 0, 0, 0, 0, 0, 3, 0, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    };

WorldMap myMap(worldMap);

static bool mapHasWall(int x, int y) {
  if (x < 0 || x >= 10 || y < 0 || y >= 7) return false;
  return (worldMap[y][x] != 0);
}

static bool mapHasXDoor(int x, int y) {
  if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;
  return (worldMap[y][x] == 3);
}

double door_closedPercentage = 1;
bool door_open = false;


static std::tuple<int, int> getTileSteps(double dir) {
  if ((0 > dir) && (dir >= -90)) {
    return std::make_pair(1, -1);
  } else if ((-90 > dir) && (dir >= -180)) {
    return std::make_pair(-1, -1);
  } else if ((-180 > dir) && (dir >= -270)) {
    return std::make_pair(-1, 1);
  } else {
    return std::make_pair(1, 1);
  }
}

void RayCaster::cast2D(SdlRenderer& renderer, double x
  , double y, double dirAngle, ClientSettings& settings) {
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderClear();
  // Dibujar mapa
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
      if (mapHasWall(i, j)) {
        renderer.setRenderDrawColor(255, 100, 100, 255);
        renderer.renderFillRect(i*64, j*64, 64, 64);
      }
      renderer.setRenderDrawColor(0, 0, 0, 255);
      renderer.renderDrawRect(i*64, j*64, 64, 64);
    }
  }

  double dAngle = settings.fov / settings.screenWidth;
  int actorX = int(x);
  double actorDX = x - actorX;
  int actorY = int(y);
  double actorDY = y - actorY;

  for (int rayNumber = 0; rayNumber < settings.screenWidth; rayNumber++) {
    double x = actorX;
    double y = actorY;
    double dx = actorDX;
    double dy = actorDY;

    double rayAngle = dirAngle + (rayNumber * dAngle) - settings.fov/2;

    double xStep, yStep, xIntercept, yIntercept;
    int tileStepX, tileStepY;
    if (rayAngle >= 0) {
      rayAngle -= 360;
    } else if (rayAngle < -360) {
      rayAngle +=360;
    }

    std::tie(tileStepX, tileStepY) = getTileSteps(rayAngle);

    if (rayAngle == -360) {
      xStep = 60;
      yStep = 0;
    } else if (rayAngle == -180) {
      xStep = -60;
      yStep = 0;
    } else if (rayAngle == -90) {
      xStep = 0;
      yStep = -60;
    } else if (rayAngle == -270) {
      xStep = 0;
      yStep = 60;
    } else {
      xStep = tileStepY/tan(rayAngle * M_PI/180.0);
      yStep = tileStepX*tan(rayAngle * M_PI/180.0);
    }

    if (rayAngle <= -180) {
      xIntercept = x + dx + (1-dy)*xStep;
    } else {
      xIntercept = x + dx + dy*xStep;
    }

    if (rayAngle <= -90 && rayAngle >= -270) {
      yIntercept = y + dy + (dx)*yStep;
    } else {
      yIntercept = y + dy + (1-dx)*yStep;
    }

    // Loopea hasta encontrar pared
    bool wallFoundX = false;
    bool wallFoundY = false;
    for (int i = 0; i <= MAX_DEPTH && !(wallFoundX && wallFoundY) ; i++) {
      if (!wallFoundX) {
        if (mapHasWall(int(xIntercept), y+tileStepY)) {
          wallFoundX = true;
        } else {
          y += tileStepY;
          xIntercept += xStep;
        }
      }
      if (!wallFoundY) {
        if (mapHasWall(x+tileStepX, int(yIntercept))) {
          wallFoundY = true;
          if (mapHasXDoor(x+tileStepX, int(yIntercept))) {
            x += tileStepX * 0.5;
            yIntercept += yStep * 0.5;
          }
        } else {
          x += tileStepX;
          yIntercept += yStep;
        }
      }
    }

    double d1 = settings.distance(actorX+actorDX, actorY+actorDY, xIntercept, y+int(tileStepY==1));
    double d2 = settings.distance(actorX+actorDX, actorY+actorDY, x+int(tileStepX==1), yIntercept);
    renderer.setRenderDrawColor(100, 100, 100, 255);
    if (d1 < d2) {
      renderer.renderDrawLine((actorX+actorDX)*64 , (actorY+actorDY)*64, xIntercept*64 , (y+int(tileStepY==1))*64);
    } else {
      renderer.renderDrawLine((actorX+actorDX)*64 , (actorY+actorDY)*64, (x+int(tileStepX==1))*64 , (yIntercept)*64);
    }
  }
}

void RayCaster::cast3D(SdlRenderer& renderer, double x, double y,
   double dirAngle, SdlTexture& walls, double zBuffer[],
   ClientSettings& settings) {

  // Piso
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  // Techo
  renderer.setRenderDrawColor(150, 150, 150, 255);
  renderer.renderFillRect(0, 0, settings.screenWidth, settings.screenHeight/2);

  double dAngle = settings.fov / settings.screenWidth;
  int actorX = int(x);
  double actorDX = x - actorX;
  int actorY = int(y);
  double actorDY = y - actorY;

  for (int rayNumber = 0; rayNumber < settings.screenWidth; rayNumber++) {
    double x = actorX;
    double y = actorY;
    double dx = actorDX;
    double dy = actorDY;

    double rayAngle = dirAngle + (rayNumber * dAngle) - settings.fov/2;

    double xStep, yStep, xIntercept, yIntercept;
    int tileStepX, tileStepY;
    if (rayAngle >= 0) {
      rayAngle -= 360;
    } else if (rayAngle < -360) {
      rayAngle +=360;
    }

    std::tie(tileStepX, tileStepY) = getTileSteps(rayAngle);


    if (rayAngle == -360) {
      xStep = 60;
      yStep = 0;
    } else if (rayAngle == -180) {
      xStep = -60;
      yStep = 0;
    } else if (rayAngle == -90) {
      xStep = 0;
      yStep = -60;
    } else if (rayAngle == -270) {
      xStep = 0;
      yStep = 60;
    } else {
      xStep = tileStepY/tan(rayAngle * M_PI/180.0);
      yStep = tileStepX*tan(rayAngle * M_PI/180.0);
    }

    if (rayAngle <= -180) {
      xIntercept = x + dx + (1-dy)*xStep;
    } else {
      xIntercept = x + dx + dy*xStep;
    }

    if (rayAngle <= -90 && rayAngle >= -270) {
      yIntercept = y + dy + (dx)*yStep;
    } else {
      yIntercept = y + dy + (1-dx)*yStep;
    }

    // Distancia de la pared
    double distortedDist;

    // Loopea hasta encontrar pared
    const Tile* wallFoundX = NULL;
    const Tile* wallFoundY = NULL;

    double door_offsetclip = 0;
    for (int i = 0; i <= MAX_DEPTH && !(wallFoundX && wallFoundY) ; i++) {
      if (!wallFoundX) {
        const Tile* wallFound = myMap.getTile(int(xIntercept), y+tileStepY);
        if (wallFound) {
          wallFoundX = wallFound;
        } else {
          y += tileStepY;
          xIntercept += xStep;
        }
      }

      if (!wallFoundY) {
        const Tile* wallFound = myMap.getTile(x+tileStepX, int(yIntercept));
        if (wallFound) {
          // Chequeo si es una puerta en X.
          if (const XDoorTile* xDoorFound = dynamic_cast<const XDoorTile*> (wallFound)) {
            double auxyIntercept = yIntercept + yStep * xDoorFound->door_depth;
            // Chequeo si el rayo choca con la puerta en ese punto
            if (double(auxyIntercept - int(auxyIntercept)) > xDoorFound->getClosedPercentage()) {
              wallFoundY = wallFound;
              door_offsetclip = xDoorFound->getClosedPercentage();
              x += tileStepX * xDoorFound->door_depth;
              yIntercept += yStep * xDoorFound->door_depth;
            }
            else {
              x += tileStepX;
              yIntercept += yStep;
            }
          }
          else {
            wallFoundY = wallFound;
          }

        } else {
          x += tileStepX;
          yIntercept += yStep;
        }
      }
    }

    double d1 = settings.distance(actorX+actorDX, actorY+actorDY, xIntercept, y+int(tileStepY==1));
    double d2 = settings.distance(actorX+actorDX, actorY+actorDY, x+int(tileStepX==1), yIntercept);

    int texture_id;
    SDL_Rect clip;
    if (d1 < d2) {
        distortedDist = d1;
        clip = wallFoundX->getClip();
        clip.x += (xIntercept-int(xIntercept))*64;
    } else {
        distortedDist = d2;
        clip = wallFoundY->getClip();
        clip.x += (yIntercept-int(yIntercept) - door_offsetclip)*64;
    }
    clip.w = 1;
    // Distancia proyectada a la camara
    double proy = distortedDist * cos((dirAngle - rayAngle)*M_PI/180);
    double scale = (1/proy) * settings.screenHeight / clip.h;

    zBuffer[rayNumber] = distortedDist;

    //int color = (255-distortedDist*10);
    //walls.setColorMod(color, color, color);

    renderer.renderCopyCentered(walls, &clip, rayNumber, settings.screenHeight/2, 1, scale);


  }
}
