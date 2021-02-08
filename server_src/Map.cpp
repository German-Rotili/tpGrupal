#include "Map.h"
#include <algorithm>
#include <iostream>
#include <iterator>

bool Map::valid_position(int x, int y) { return true; }

void Map::add_player(char id) {
  this->players.push_back(Player(*this, this->config, id));
}

std::map<int, std::map<int, Door>> &Map::get_doors() 
{
  return this->doors;
}

void Map::add_rocket(Rocket rocket) { this->rockets.push_back(rocket); }

void Map::tick() {
  for (Player &player : this->players) {
    player.tick();
  }
  for (Rocket &rocket : this->rockets) {
    auto i = std::begin(this->rockets);
    while (i != this->rockets.end()) {
      if (i->tick()) {
        i = this->rockets.erase(i);
      } else {
        i++;
      }
    }
  }
}

bool Map::valid_position(int x, int y) {
  char squareId = this->get_id(x, y);
  if (this->is_solid(squareId)) {
    return true;
  }
  if (this->is_door(squareId)) {
    return this->doors[x][y].is_walkable(); //
  }
}

bool Map::is_impactable(int x, int y) {
  char squareId = this->get_id(x, y);
  return (this->is_solid(squareId));
}

Map::~Map() {}

char Map::get_id(int x, int y) {}

bool Map::is_solid(char id) {
  if (id >= 0 && id <= 33) {
    return true;
  }
  if (id >= 36 && id <= 39) {
    return true;
  }
  return false;
}

bool Map::is_door(char id) {
  return (id == 34 || id == 35 || (id >= 59 && id <= 62));
}

Map::Map(std::vector<std::vector<int>> map) : map{map}{
  
}

void Map::populate_variables() {
  for (int x = 0; x < this->map.size(); x++) {
    for (int y = 0; y < this->map[y].size(); y++) {

      if (this->is_door(this->get_id(x, y))) {
        this->doors[x][y] = Door(this->get_id(x, y));
      }
      if (this->is_spawn(this->get_id(x, y))) {
        for (Player &player : this->players) {
          if (!player.is_placed()) {
            player.set_spawn(x, y);
          }
        }
      }
    }
  }
}
