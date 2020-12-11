#include "rayCaster.h"
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <utility>
#include <tuple>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"

#define MAX_DEPTH 8

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SIZE_NIVEL 5
int worldMap[7][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 1, 0, 1, 1, 1, 0, 1},
                      {1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
                      {1, 0, 0, 1, 1, 1, 0, 1, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    };

static bool mapHasWall(int x, int y) {
  if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;
  return (worldMap[y][x] == 1);
}


static double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

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

void RayCaster::cast2D(SdlRenderer& renderer, double dirAngle, double x, double y, double FOV) {
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

  double dAngle = FOV / SCREEN_WIDTH;
  int actorX = int(x);
  double actorDX = x - actorX;
  int actorY = int(y);
  double actorDY = y - actorY;

  for (int rayNumber = 0; rayNumber < SCREEN_WIDTH; rayNumber++) {
    int x = actorX;
    int y = actorY;
    double dx = actorDX;
    double dy = actorDY;

    double rayAngle = dirAngle + (rayNumber * dAngle) - FOV/2;

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
      xStep = tileStepY/tan(rayAngle * PI/180.0);
      yStep = tileStepX*tan(rayAngle * PI/180.0);
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
        } else {
          x += tileStepX;
          yIntercept += yStep;
        }
      }
    }

    double d1 = distance(actorX+actorDX, actorY+actorDY, xIntercept, y+int(tileStepY==1));
    double d2 = distance(actorX+actorDX, actorY+actorDY, x+int(tileStepX==1), yIntercept);
    renderer.setRenderDrawColor(100, 100, 100, 255);
    if (d1 < d2) {
      renderer.renderDrawLine((actorX+actorDX)*64 , (actorY+actorDY)*64, xIntercept*64 , (y+int(tileStepY==1))*64);
      distortedDist = d1;
    } else {
      renderer.renderDrawLine((actorX+actorDX)*64 , (actorY+actorDY)*64, (x+int(tileStepX==1))*64 , (yIntercept)*64);
      distortedDist = d2;
    }
  }

}

void RayCaster::cast3D(SdlRenderer& renderer, double dirAngle, double x, double y, double FOV) {
  // Piso
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  // Techo
  renderer.setRenderDrawColor(150, 150, 150, 255);
  renderer.renderFillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2);

  double dAngle = FOV / SCREEN_WIDTH;
  double proyPlaneDist = 160/tan(30*PI/180);
  int actorX = int(x);
  double actorDX = x - actorX;
  int actorY = int(y);
  double actorDY = y - actorY;

  for (int rayNumber = 0; rayNumber < SCREEN_WIDTH; rayNumber++) {
    int x = actorX;
    int y = actorY;
    double dx = actorDX;
    double dy = actorDY;

    double rayAngle = dirAngle + (rayNumber * dAngle) - FOV/2;

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
      xStep = tileStepY/tan(rayAngle * PI/180.0);
      yStep = tileStepX*tan(rayAngle * PI/180.0);
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
        } else {
          x += tileStepX;
          yIntercept += yStep;
        }
      }
    }

    double d1 = distance(actorX+actorDX, actorY+actorDY, xIntercept, y+int(tileStepY==1));
    double d2 = distance(actorX+actorDX, actorY+actorDY, x+int(tileStepX==1), yIntercept);

    if (d1 < d2) {
        distortedDist = d1;
    } else {
        distortedDist = d2;
    }

    // Distancia proyectada a la camara
    double proy = distortedDist * cos((dirAngle - rayAngle)*PI/180);
    int wallHeight = (1/proy) * 255;

    renderer.setRenderDrawColor(255, log2(wallHeight+1)*255/15, log2(wallHeight+1)*255/15, 255);
    renderer.renderFillRect(rayNumber, (SCREEN_HEIGHT/2)-(wallHeight/2), 1, wallHeight);
  }
}
