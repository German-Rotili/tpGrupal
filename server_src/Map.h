#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <map>
#include "Config.h"
class Rocket;
class Action;
class Door;
class Player;

class GamePlay;
#include "./weapons/Rocket.h"
#include "../common_src/Action.h"
#include "Player.h"
#include "Door.h"
class Map {
private:
  std::vector<Player*> players;
  std::vector<Rocket> rockets;
  std::vector<Action> actions;
  std::vector<std::vector<int>> map;
  std::vector<char> raw_map;
  std::map<int, std::map<int, Door>> doors;
  std::map<int, std::map<int, char>> items;

  Config config;


  /*
  esto pone los jugadores en sus lugares y carga las puertas y paredes especiales. 
  */
  void populate_variables();
  bool is_solid(int id);
  bool is_door(int id);
  bool is_spawn(int id);
  
  

public:
  Map( std::vector<char> raw_map);
  ~Map();

  int get_id(int x, int y);
  void add_player(int id);   // ver quien hace los players
  std::vector<Player*> &get_players(); // placeholder
  std::map<int, std::map<int, Door>> get_doors();

  void start();
  void add_rocket(Rocket Rocket);
  bool is_item(char id);

  bool valid_position(int x, int y);
  bool is_impactable(int x, int y);

  void tick();
  void remove_item(int x, int y);
  void execute_intentions(std::vector<char> & intentions, int & client_id);

  std::vector<char> get_raw_map();

  void add_action(int player_id, float weapon_id, float posx, float posy);
  
  friend class GamePlay;
};


#endif // __MAP_H__