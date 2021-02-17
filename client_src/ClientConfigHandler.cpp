#include <string>
#include <iostream>
#include <fstream>
#include "ClientConfigHandler.h"

ClientConfigHandler::ClientConfigHandler(std::string path):
  root(YAML::LoadFile(path)) {}

ClientConfigHandler::~ClientConfigHandler() {}

int ClientConfigHandler::getHeight() {
  int height = root["height"].as<int>();
  return height;
}

int ClientConfigHandler::getWidth() {
  int width = root["width"].as<int>();
  return width;
}

int ClientConfigHandler::getFOV() {
  int FOV = root["FOV"].as<int>();
  return FOV;
}

bool ClientConfigHandler::getFullscreen() {
  bool fullscreen = root["fullscreen"].as<bool>();
  return fullscreen;
}
