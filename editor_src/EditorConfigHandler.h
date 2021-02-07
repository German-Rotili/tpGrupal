#ifndef EDITORCONFIGHANDLER
#define EDITORCONFIGHANDLER

#include <iostream>
#include <string>
#include "yaml-cpp/yaml.h"

class EditorConfigHandler {
private:
  YAML::Node root;

public:
  void initConfig(std::string path);

  int getY();

  int getX();
};
#endif /* EDITORCONFIGHANDLER */
