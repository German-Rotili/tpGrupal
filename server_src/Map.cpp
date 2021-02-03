#include "Map.h"
#include <iostream>

bool Map::valid_position(int pos_x, int pos_y) { return true; }

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

void Map::add_player(Player &player) { this->players.push_back(player); }

void Map::add_rocket(Rocket rocket) { this->rockets.push_back(rocket); }

Map::~Map() {}
