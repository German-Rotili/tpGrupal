#include "MapHandler.h"
#include "pathsConfig.h"
#include <string>
#include <iostream>
#include <fstream>

void MapHandler::emitMap(std::string path, std::vector<std::vector<int>> map) {
  std::string actualPath = CONFIG_PATH + path + ".yaml";
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
  std::string actualPath = CONFIG_PATH + path + ".yaml";
  YAML::Node root = YAML::LoadFile(actualPath);

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

std::vector<std::vector<int>> MapHandler::readMapFromString(std::string file) {
  YAML::Node root = YAML::Load(file);
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

void MapHandler::generateMapList(std::string path) {
  YAML::Node root = YAML::LoadFile(MAP_LIST_PATH);
  std::string actualPath = path + ".yaml";

  int mapAmount = root["amount"].as<int>();

  std::vector<std::string> paths = std::vector<std::string>(mapAmount, "");

  for (int i = 0; i < mapAmount; i++) {
    paths[i] = root[i].as<std::string>();
  }

  std::ofstream outfile(MAP_LIST_PATH);
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "amount";
  out << YAML::Value << (paths.size()+1);

  for (int i = 0; i < mapAmount; i++) {
    out << YAML::Key << std::to_string(i);
    out << YAML::Value << paths[i];
  }

  out << YAML::Key << std::to_string(mapAmount);
  out << YAML::Value << path;
  out << YAML::EndMap;

  outfile << out.c_str();
  outfile.close();
}

std::vector<std::string> MapHandler::getMapList() {
  YAML::Node root = YAML::LoadFile(MAP_LIST_PATH);

  int mapAmount = root["amount"].as<int>();

  std::vector<std::string> maps = std::vector<std::string>(mapAmount, "");

  for (int i = 0; i < mapAmount; i++) {
    maps[i] = root[i].as<std::string>();
  }

  // Hago un purge de mapas inválidos.
  for (std::vector<std::string>::iterator it = maps.begin();
  it != maps.end(); it++) {
    try {
      (this->readMap(*it));
    } catch (std::exception const& e) {
      maps.erase(it);
      --it;
    }
  }

  return maps;
}
