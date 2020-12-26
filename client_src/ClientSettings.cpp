#include "ClientSettings.h"

#include <cmath>

ClientSettings::ClientSettings(int screenWidth, int screenHeight, int fps, int fov):
  screenWidth(screenWidth),
  screenHeight(screenHeight),
  fps(fps),
  fov(fov) {}

ClientSettings::~ClientSettings() {}

// Seguramente haya que mover PI y distance a clase aparte.
float ClientSettings::distance(float x1, float y1, float x2, float y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}
