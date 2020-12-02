#include "rayCasting.h"
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void RayCasting::run() {
  // El FOV va a venir por configuración
  double FOV = 60;
  double dAngle = FOV / screenWidth;

  for (int rayNumber = 0; rayNumber < screenWidth; rayNumber++) {
    bool sideWall = false;  // Se fija si es una
                           // pared vertical con respecto al map
    double rayAngle = dirAngle + (rayNumber * dAngle) - FOV/2;

    double xIntercept = actorGlobalX + (actorX - actorGlobalX) +
                 (-(actorY - actorGlobalY))/tan(rayAngle);
    double yIntercept = actorGlobalY + (actorY - actorGlobalY) +
                 (actorX - actorGlobalX)/tan(rayAngle);

    int tileStepX = 1;
    int tileStepY = 1;
    double stepX = 1/tan(rayAngle);
    double stepY = tan(rayAngle);

    // Distancia de la pared
    double distX, distY;

    // Loopea hasta encontrar pared
    bool wallFound = false;

    if (hasWall(worldMap[actorX][int(yIntercept)]) && !wallFound) {
      sideWall = false;
      wallFound = true;
    } else {
      x += tileStepX;
      yIntercept += yStep;
    }

    if (hasWall(worldMap[int(xIntercept)][actorY]) && !wallFound) {
      sideWall = true;
      wallFound = true;
    } else {
      y += tileStepY;
      xIntercept += xStep;
    }

    while (!wallFound) {
      if (yIntercept < y) {
        sideWall = false;
        if (hasWall(worldMap[x][int(yIntercept)])) {
          wallFound = true;
        } else {
          x += tileStepX;
          yIntercept += yStep;
        }
      } else if (xIntercept < x) {
        sideWall = true;
        if (hasWall(worldMap[int(xIntercept)][y])) {
          wallFound = true;
        } else {
          y += tileStepY;
          xIntercept += xStep;
        }
      }
    }

    // Dependiendo de si es vert u hori que distancias agarro
    if (sideWall) {
      distX = xIntercept - actorX;
      distY = y - actorY;
    } else {
      distX = x - actorX;
      distY = yIntercept- actorY;
    }

    // Distancia proyectada a la camara
    double proy = (distX * cos(rayAngle)) + (distY * sin(rayAngle));
  }
}
