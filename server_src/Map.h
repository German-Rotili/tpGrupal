#ifndef __SERVER_MAP_H__
#define __SERVER_MAP_H__
#include "./weapons/Rocket.h"
#include "Constants.h"
#include "Player.h"
#include <vector>
#include <Door.h>
#include "Config.h"

class Map {
private:
  std::vector<Player> players;
  std::vector<Rocket> rockets;
  std::vector<std::vector<int>> map;
  std::map<int, std::map<Door>> doors;
  Config config;


  /*
  esto pone los jugadores en sus lugares y carga las puertas y paredes especiales. 
  */
  void populate_variables();
  char get_id(int x, int y);
  bool is_solid(char id);
  bool is_door(char id);
  bool is_spawn(char id);
  

public:
  Map();
  ~Map();

  void add_player(char id);     // ver quien hace los players
  std::vector<Player &> get_players(); // placeholder
  void add_rocket(Rocket Rocket);
  int has_item();

  bool valid_position(int x, int y);
  bool is_impactable(int x, int y);

  void tick();
  void execute_intentions();
};

#endif // __SERVER_MAP_H__