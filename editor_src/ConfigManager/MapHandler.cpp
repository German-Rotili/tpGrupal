#include "MapHandler.h"
#include <string>
#include <iostream>
#include <fstream>

void MapHandler::emitMap(std::string path, std::vector<std::vector<int>> map) {
  std::string actualPath = "config/" + path + ".yaml";
  std::ofstream outfile (actualPath);
  YAML::Emitter out;

  int y = map.size();
  int x = map.at(0).size();

  out << YAML::BeginMap;
  out << YAML::Key << "x";
  out << YAML::Value << x;
  out << YAML::Key << "y";
  out << YAML::Value << y;

  for (int i = 0; i < y; i++) {
    out << YAML::Key << std::to_string(i);
    out << YAML::BeginSeq;
    for (int j = 0; j < x; j++) {
      out << map.at(i).at(j);
    }
    out << YAML::EndSeq;
  }
  out << YAML::EndMap;

  outfile << out.c_str();
  outfile.close();
}

std::vector<std::vector<int>> MapHandler::readMap(std::string path) {
  YAML::Node root = YAML::LoadFile(path);

  int x = root["x"].as<int>();
  int y = root["y"].as<int>();

  std::vector<std::vector<int>> map =
  std::vector<std::vector<int>>(y, std::vector<int>(x, 0));

  for (int i = 0; i < y; i++) {
    const YAML::Node& current_y = root[std::to_string(i)];
    for (int j = 0; j < x; j++) {
      map[i][j] = current_y[j].as<int>();
    }
  }

  return map;
}
