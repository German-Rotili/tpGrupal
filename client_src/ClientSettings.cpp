#include "ClientSettings.h"

#include <cmath>

ClientSettings::ClientSettings(int screenWidth, int screenHeight, int fps, int fov):
  screenWidth(screenWidth),
  screenHeight(screenHeight),
  fps(fps),
  fov(fov) {}

ClientSettings::~ClientSettings() {}

// Seguramente haya que mover distance a clase aparte.
double ClientSettings::distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}
