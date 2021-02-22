#ifndef SERVERCONFIGHANDLER
#define SERVERCONFIGHANDLER

#include <iostream>
#include <string>
#include "yaml-cpp/yaml.h"
#include "../common_src/structDefinitions.h"

class ServerConfigHandler {
private:
  YAML::Node root;

public:
  ServerConfigHandler();
  void initConfig(std::string path);

  weaponStats_t getWeaponStats(WeaponType type);

  actorStats_t getPlayerStats();
};
#endif /* SERVERCONFIGHANDLER */
