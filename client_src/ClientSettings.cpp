#include "ClientSettings.h"


#include <math.h>

ClientSettings::ClientSettings(int screenWidth, int screenHeight, int fov, float pi):
  screenWidth(screenWidth),
  screenHeight(screenHeight),
  fov(fov),
  pi(pi) {}

ClientSettings::~ClientSettings() {}

// Seguramente haya que mover PI y distance a clase aparte.
float ClientSettings::distance(float x1, float y1, float x2, float y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}
