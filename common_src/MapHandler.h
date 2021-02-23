#ifndef MAPHANDLER
#define MAPHANDLER

#include <iostream>
#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"

class MapHandler {
public:
  void emitMap(std::string path, std::vector<std::vector<int>> map);

  std::vector<std::vector<int>> readMap(std::string path);
  std::vector<std::vector<int>> readMapFromString(std::string file);
  int getSpawns(std::string path);

  void generateMapList(std::string path);

  std::vector<std::string> getMapList();
};
#endif /* MAPHANDLER */
