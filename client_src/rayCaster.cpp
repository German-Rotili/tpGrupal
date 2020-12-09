#include "rayCaster.h"
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PI 3.14

#define SIZE_NIVEL 5
int worldMap[7][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
                      {1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    };

bool mapHasWall(int x, int y) {
  if (x < 0 || x >= 10 || y < 0 || y >= 10) return true;
  return (worldMap[y][x] == 1);
}


double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

void cast2D(SdlRenderer *renderer, double dirAngle, int actorX, int actorY, double actorDX, double actorDY, double FOV) {
  renderer->setRenderDrawColor(255, 255, 255, 255);
  renderer->renderClear();
  // Dibujar mapa
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
      if (mapHasWall(i, j)) {
        renderer->setRenderDrawColor(255, 100, 100, 255);
        renderer->renderFillRect(i*64, j*64, 64, 64);
      }
      renderer->setRenderDrawColor(0, 0, 0, 255);
      renderer->renderDrawRect(i*64, j*64, 64, 64);
    }
  }

  double dAngle = FOV / SCREEN_WIDTH;

  for (int rayNumber = 0; rayNumber < SCREEN_WIDTH; rayNumber++) {
    int x = actorX;
    int y = actorY;
    double dx = actorDX;
    double dy = actorDY;

    double rayAngle = dirAngle + (rayNumber * dAngle) - FOV/2;

    double xStep;
    double yStep;
    double xIntercept;
    double yIntercept;
    int tileStepX;
    int tileStepY;

    if (0 > rayAngle >= -90) {
      tileStepX = 1;  // (1, -1) para 0 a 90, (-1, -1) para 90 a 180, (-1, 1) para 180 a 270 y (1, 1) para 270 a 360
      tileStepY = -1;
      xStep = -tileStepX/tan(rayAngle * PI/180.0);
      yStep = -tileStepY*tan(rayAngle * PI/180.0);
    } else if (-90 > rayAngle >= -180) {
      tileStepX = -1;  // (1, -1) para 0 a 90, (-1, -1) para 90 a 180, (-1, 1) para 180 a 270 y (1, 1) para 270 a 360
      tileStepY = -1;
      xStep = tileStepX/tan(rayAngle * PI/180.0);
      yStep = tileStepY*tan(rayAngle * PI/180.0);
    } else if (-180 > rayAngle >= -270) {
      tileStepX = -1;
      tileStepY = 1;
      xStep = -tileStepX*tan(rayAngle * PI/180.0);
      yStep = -tileStepY/tan(rayAngle * PI/180.0);
    } else if (-270 > rayAngle >= -360) {
      tileStepX = 1;
      tileStepY = 1;
      xStep = tileStepX*tan(rayAngle * PI/180.0);
      yStep = tileStepY/tan(rayAngle * PI/180.0);
    }

    if (rayAngle == -360){
      xStep = 60;
      yStep = 0;
    } else if (rayAngle == -180){
      xStep = -60;
      yStep = 0;
    } else if (rayAngle == -90){
      xStep = 0;
      yStep = -60;
    } else if (rayAngle == -270){
      xStep = 0;
      yStep = 60;
    }
    xIntercept = x + dx + (dy)*xStep;
    yIntercept = y + dy + dx*yStep;


    // Distancia de la pared
    double distortedDist;

    // Loopea hasta encontrar pared
    bool wallFoundX = false;
    bool wallFoundY = false;
    for (int i = 0; i <= 8 && !(wallFoundX && wallFoundY) ; i++) {
      if (!wallFoundX) {
        if (mapHasWall(int(xIntercept), y+tileStepY)) {
          wallFoundX = true;
        }
        else{
          y += tileStepY;
          xIntercept += xStep;
        }
      }
      if (!wallFoundY) {
        if (mapHasWall(x+tileStepX, int(yIntercept))) {
          wallFoundY = true;
        }
        else{
          x += tileStepX;
          yIntercept += yStep;
        }
      }
    }

    double d1 = distance(actorX+actorDX, actorY+actorDY, xIntercept, y);
    double d2 = distance(actorX+actorDX, actorY+actorDY, x+tileStepX, yIntercept);

    if (wallFoundX || wallFoundY){
      renderer->setRenderDrawColor(100, 100, 100, 255);
      if (d1 < d2) {
        renderer->renderDrawLine((actorX+actorDX)*64 , (actorY+actorDY)*64, xIntercept*64 , y*64);
      } else {
        renderer->renderDrawLine((actorX+actorDX)*64 , (actorY+actorDY)*64, (x+tileStepX)*64 , (yIntercept)*64);
      }
    }
    //Lineas interseccion eje horizontal
    renderer->setRenderDrawColor(0, 0, 0, 0xFF);

    renderer->setRenderDrawColor(0xFF, 0x00, 0x00, 0x00);
    renderer->renderDrawLine((actorX) * 64, (actorY+actorDY) * 64, (actorX+actorDX) * 64, (actorY+actorDY) * 64);
    renderer->renderDrawLine((actorX+actorDX) * 64, (actorY) * 64, (actorX+actorDX) * 64, (actorY+actorDY) * 64);
  }
}

void cast3D(SdlRenderer *renderer, double dirAngle, int actorX, int actorY, double actorDX, double actorDY, double FOV) {
  // Piso
  renderer->setRenderDrawColor(100, 100, 100, 255);
  renderer->renderClear();

  // Techo
  renderer->setRenderDrawColor(150, 150, 150, 255);
  renderer->renderFillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2);

  double dAngle = FOV / SCREEN_WIDTH;
  double proyPlaneDist = 160/tan(30*PI/180);

  for (int rayNumber = 0; rayNumber < SCREEN_WIDTH; rayNumber++) {
    int x = actorX;
    int y = actorY;
    double dx = actorDX;
    double dy = actorDY;

    double rayAngle = dirAngle + (rayNumber * dAngle) - FOV/2;

    double xStep;
    double yStep;
    double xIntercept;
    double yIntercept;
    int tileStepX;  // (1, -1) para 0 a 90, (-1, 1) para 90 a 180, (-1, -1) para 180 a 270 y (1, 1) para 270 a 360
    int tileStepY;

    if (0 > rayAngle >= -90) {
      tileStepX = 1;  // (1, -1) para 0 a 90, (-1, -1) para 90 a 180, (-1, 1) para 180 a 270 y (1, 1) para 270 a 360
      tileStepY = -1;
      xStep = -tileStepX/tan(rayAngle * PI/180.0);
      yStep = -tileStepY*tan(rayAngle * PI/180.0);
    } else if (-90 > rayAngle >= -180) {
      tileStepX = -1;  // (1, -1) para 0 a 90, (-1, -1) para 90 a 180, (-1, 1) para 180 a 270 y (1, 1) para 270 a 360
      tileStepY = -1;
      xStep = tileStepX/tan(rayAngle * PI/180.0);
      yStep = tileStepY*tan(rayAngle * PI/180.0);
    } else if (-180 > rayAngle >= -270) {
      tileStepX = -1;
      tileStepY = 1;
      xStep = -tileStepX*tan(rayAngle * PI/180.0);
      yStep = -tileStepY/tan(rayAngle * PI/180.0);
    } else if (-270 > rayAngle >= -360) {
      tileStepX = 1;
      tileStepY = 1;
      xStep = tileStepX*tan(rayAngle * PI/180.0);
      yStep = tileStepY/tan(rayAngle * PI/180.0);
    }

    if (rayAngle == -360){
      xStep = 60;
      yStep = 0;
    } else if (rayAngle == -180){
      xStep = -60;
      yStep = 0;
    } else if (rayAngle == -90){
      xStep = 0;
      yStep = -60;
    } else if (rayAngle == -270){
      xStep = 0;
      yStep = 60;
    }
    xIntercept = x + dx + (dy)*xStep;
    yIntercept = y + dy + dx*yStep;

    // Distancia de la pared
    double distortedDist;

    // Loopea hasta encontrar pared
    bool wallFoundX = false;
    bool wallFoundY = false;
    for (int i = 0; i <= 8 && !(wallFoundX && wallFoundY) ; i++) {
      if (!wallFoundX) {
        if (mapHasWall(int(xIntercept), y+tileStepY)) {
          wallFoundX = true;
        }
        else{
          y += tileStepY;
          xIntercept += xStep;
        }
      }
      if (!wallFoundY) {
        if (mapHasWall(x+tileStepX, int(yIntercept))) {
          wallFoundY = true;
        }
        else{
          x += tileStepX;
          yIntercept += yStep;
        }
      }
    }

    double d1 = distance(actorX+actorDX, actorY+actorDY, xIntercept, y);
    double d2 = distance(actorX+actorDX, actorY+actorDY, x+tileStepX, yIntercept);

    if (wallFoundX || wallFoundY){
      if (d1 < d2) {
        distortedDist = d1;
      } else {
        distortedDist = d2;
      }
    }

    // Distancia proyectada a la camara
    double proy = distortedDist * cos((dirAngle - rayAngle)*PI/180);
    int wallHeight = (1/proy) * 255;

    renderer->setRenderDrawColor(255, wallHeight, wallHeight, 255);
    renderer->renderFillRect(rayNumber, (SCREEN_HEIGHT/2)-(wallHeight/2), 1, wallHeight);
  }
}
