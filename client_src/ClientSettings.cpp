#include "ClientSettings.h"

#include <cmath>

ClientSettings::ClientSettings(int screenWidth, int screenHeight, int fps, int fov):
  screenWidth(screenWidth),
  screenHeight(screenHeight),
  fps(fps),
  fov(fov) {}

ClientSettings::~ClientSettings() {}
