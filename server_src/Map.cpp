#include "Map.h"
#include "Door.h"
#include "./weapons/Rocket.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include "../common_src/MapHandler.h"
#include "../common_src/Action.h"
#include "Constants.h"
#include "GamePlay.h"
#include "Player.h"
#include "Config.h"
#include <map>



void Map::add_player(char id) {
  this->players.push_back(Player(this, &(this->config), id));
}

std::vector<Player>& Map::get_players() 
{
  return this->players;
}

std::map<int, std::map<int, Door>> Map::get_doors() 
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

std::vector<char> Map::get_raw_map(){
  return this->raw_map;
}


void Map::remove_item(int x, int y) {
  this->map[x][y] = EMPTY;
  this->items[x].erase(y);
}

bool Map::is_item(char id) 
{
  return(id <= 56 && id >= 46);
}

bool Map::valid_position(int x, int y) {
  char squareId = this->get_id(x, y);
  if (this->is_solid(squareId)) {
    return true;
  }
  if (this->is_door(squareId)) {
    this->doors.find(x)->second.find(y)->second.is_walkable();
  }
  return false;
}

bool Map::is_impactable(int x, int y) {
  char squareId = this->get_id(x, y);
  return (this->is_solid(squareId));
}

Map::~Map() {}

char Map::get_id(int x, int y) {
  return this->map[x][y];
}

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

Map::Map(  std::vector<char> raw_map) : raw_map{raw_map}{
  std::string map_aux(raw_map.data());
  MapHandler handler;
  map = handler.readMapFromString(map_aux);

}

void Map::populate_variables() {

  for (int x = 0; x < this->map.size(); x++) {
    for (int y = 0; y < this->map[y].size(); y++) {
      char id = this->get_id(x,y);

      if (this->is_door(id)) {
        this->doors[x].insert(std::pair<int,Door>(y,Door(id)));
      }
      if (this->is_spawn(id)) {
        for (Player &player : this->players) {
          if (!player.is_placed()) {
            player.set_spawn(x, y);
          }
        }
      }
      if(this->is_item(id)){
        this->items[x][y] = id;
      }
    }
  }
}

void Map::execute_intentions(std::vector<char> & intentions, int & client_id){
  for (Player &player : this->players) {
    if(player.get_id() == client_id){
      for (char &i : intentions){
        player.execute_intention(i);
      }
      break;
    }
  }
}
