#ifndef CLIENTCONFIGHANDLER
#define CLIENTCONFIGHANDLER

#include <iostream>
#include <string>
#include "yaml-cpp/yaml.h"

class ClientConfigHandler {
private:
  YAML::Node root;

public:
  explicit ClientConfigHandler(std::string path);
  ~ClientConfigHandler();

  int getHeight();

  int getWidth();

  int getFOV();

  bool getFullscreen();
};
#endif /* CLIENTCONFIGHANDLER */
