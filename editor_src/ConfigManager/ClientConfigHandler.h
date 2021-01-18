#ifndef CLIENTCONFIGHANDLER
#define CLIENTCONFIGHANDLER

#include <iostream>
#include <string>
#include "yaml-cpp/yaml.h"

class ClientConfigHandler {
private:
  YAML::Node root;

public:
  void initConfig(std::string path);

  int getHeight();

  int getWidth();

  int getFOV();
};
#endif /* CLIENTCONFIGHANDLER */
