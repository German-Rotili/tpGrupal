#include <iostream>
#include <string>
#include "yaml-cpp/yaml.h"
#include "EditorConfigHandler.h"

void EditorConfigHandler::initConfig(std::string path) {
  root = YAML::LoadFile(path);
}

int EditorConfigHandler::getY() {
  int y = root["y"].as<int>();
  return y;
}

int EditorConfigHandler::getX() {
  int x = root["x"].as<int>();
  return x;
}
