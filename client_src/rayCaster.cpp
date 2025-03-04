#include "rayCaster.h"
#include <stdio.h>
#include <utility>

RayCaster::RayCaster(SdlTexture& walls, ClientSettings& settings):
  walls(walls),
  DIRECTION_PER_RAY(settings.fov / settings.screenWidth),
  HALF_SCREEN_HEIGHT(settings.screenHeight/2),
  HALF_FOV(settings.fov/2),
  TEXTURE_RELATIVE_HSCALE(settings.screenHeight / TEXTURES_HEIGHT) {
    setTileSteps(0);
}

RayCaster::~RayCaster() {}

void RayCaster::setTileSteps(double dir) {
  if ((0 > dir) && (dir >= -90)) {
    tileStepX = 1;
    tileStepY = -1;
  } else if ((-90 > dir) && (dir >= -180)) {
    tileStepX = -1;
    tileStepY = -1;
  } else if ((-180 > dir) && (dir >= -270)) {
    tileStepX = -1;
    tileStepY = 1;
  } else {
    tileStepX = 1;
    tileStepY = 1;
  }
}

void RayCaster::setXYSteps(double direction) {
  if (direction == -360) {
    xStep = 60;
    yStep = 0;
  } else if (direction == -180) {
    xStep = -60;
    yStep = 0;
  } else if (direction == -90) {
    xStep = 0;
    yStep = -60;
  } else if (direction == -270) {
    xStep = 0;
    yStep = 60;
  } else {
    double auxTanDirection = tan(direction * M_PI_180);
    xStep = tileStepY/auxTanDirection;
    yStep = tileStepX*auxTanDirection;
  }
}

void RayCaster::dibujarPisoYTecho(SdlRenderer& renderer, ClientSettings& settings) {
  // Piso
  renderer.setRenderDrawColor(112, 112, 112, 255);
  renderer.renderClear();

  // Techo
  renderer.setRenderDrawColor(56, 56, 56, 255);
  renderer.renderFillRect(0, 0, settings.screenWidth, HALF_SCREEN_HEIGHT);
}

void RayCaster::cast3D(SdlRenderer& renderer, WorldMap& myMap, Player& player,
   ClientSettings& settings) {
  dibujarPisoYTecho(renderer, settings);
  int tileX = int(player.getX());
  double dx = player.getX() - tileX;
  int tileY = int(player.getY());
  double dy = player.getY() - tileY;

  double rayAngle = player.getDirection() - HALF_FOV;

  for (int rayNumber = 0; rayNumber < settings.screenWidth; rayNumber++) {
    double x = tileX;
    double y = tileY;

    rayAngle += DIRECTION_PER_RAY;

    if (rayAngle >= 0) {
      rayAngle -= 360;
    } else if (rayAngle < -360) {
      rayAngle +=360;
    }

    setTileSteps(rayAngle);

    setXYSteps(rayAngle);

    double xIntercept, yIntercept;

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
    double xDoor_offsetclip = 0;
    double yDoor_offsetclip = 0;

    for (int i = 0; i <= MAX_DEPTH && !(wallFoundX && wallFoundY) ; i++) {
      if (!wallFoundX) {
        const Tile* wallFound = myMap.getTile(int(xIntercept), y+tileStepY);
        if (wallFound) {
          // Chequeo si es una puerta en Y.
          if (const YDoorTile* yDoorFound = dynamic_cast<const YDoorTile*> (wallFound)) {
            double auxXIntercept = xIntercept + xStep * yDoorFound->door_depth;
            // Chequeo si el rayo choca con la puerta en ese punto
            if (double(auxXIntercept - int(auxXIntercept)) > yDoorFound->getClosedPercentage()) {
              wallFoundX = wallFound;
              yDoor_offsetclip = yDoorFound->getClosedPercentage();
              y += tileStepY * yDoorFound->door_depth;
              xIntercept += xStep * yDoorFound->door_depth;
            } else {
              y += tileStepY;
              xIntercept += xStep;
            }
          } else if (const SecretYDoorTile* secretYDoorFound = dynamic_cast<const SecretYDoorTile*> (wallFound)) {
            if (secretYDoorFound->getDepthPercentage() < 1) {
              wallFoundX = wallFound;
              y += tileStepY * secretYDoorFound->getDepthPercentage();
              xIntercept += xStep * secretYDoorFound->getDepthPercentage();
            } else {
              y += tileStepY;
              xIntercept += xStep;
            }
          } else {
            wallFoundX = wallFound;
          }
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
              xDoor_offsetclip = xDoorFound->getClosedPercentage();
              x += tileStepX * xDoorFound->door_depth;
              yIntercept += yStep * xDoorFound->door_depth;
            } else {
              x += tileStepX;
              yIntercept += yStep;
            }
          } else if (const SecretXDoorTile* secretXDoorFound = dynamic_cast<const SecretXDoorTile*> (wallFound)) {
            if (secretXDoorFound->getDepthPercentage() < 1) {
              wallFoundY = wallFound;
              x += tileStepX * secretXDoorFound->getDepthPercentage();
              yIntercept += yStep * secretXDoorFound->getDepthPercentage();
            } else {
              x += tileStepX;
              yIntercept += yStep;
            }
          } else {
            wallFoundY = wallFound;
          }
        } else {
          x += tileStepX;
          yIntercept += yStep;
        }
      }
    }

    double d1 = player.getDistanceToPoint(xIntercept, y+int(tileStepY == 1));
    double d2 = player.getDistanceToPoint(x+int(tileStepX == 1), yIntercept);

    int texture_id;
    SDL_Rect clip;
    if (d1 < d2) {
        distortedDist = d1;
        if (!wallFoundX) continue;
        clip = wallFoundX->getClip();
        clip.x += (xIntercept-int(xIntercept) - yDoor_offsetclip)*clip.h;
    } else {
        distortedDist = d2;
        if (!wallFoundY) continue;
        clip = wallFoundY->getClip();
        clip.x += (yIntercept-int(yIntercept) - xDoor_offsetclip)*clip.h;
    }
    clip.w = 1;
    // Distancia proyectada a la camara
    double proy = distortedDist * cos((player.getDirection() - rayAngle)*M_PI_180);
    double scale = (1/proy) * TEXTURE_RELATIVE_HSCALE;

    zBuffer[rayNumber] = distortedDist;

    renderer.renderCopyCentered(walls, &clip, rayNumber, HALF_SCREEN_HEIGHT, 1, scale);
  }
}
