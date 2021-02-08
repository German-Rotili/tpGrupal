#ifndef __SERVER_MAP_H__
#define __SERVER_MAP_H__
#include "./weapons/Rocket.h"
#include "Constants.h"
#include "GamePlay.h"
#include "Player.h"
#include <vector>
#include <Door.h>
#include "Config.h"
class GamePlay;

class Map {
private:
  std::vector<Player> players;
  std::vector<Rocket> rockets;
  std::vector<std::vector<int>> map;
  std::map<int, std::map<int, Door>> doors;
  std::map<int, std::map<int, char>> items;

  Config config;


  /*
  esto pone los jugadores en sus lugares y carga las puertas y paredes especiales. 
  */
  void populate_variables();
  bool is_solid(char id);
  bool is_door(char id);
  bool is_spawn(char id);
  
  

public:
  Map(std::vector<std::vector<int>> map);
  ~Map();

  char get_id(int x, int y);
  void add_player(char id);   // ver quien hace los players
  std::vector<Player &> get_players(); // placeholder
  std::map<int, std::map<int, Door>>& get_doors();

  void add_rocket(Rocket Rocket);
  bool is_item(char id);

  bool valid_position(int x, int y);
  bool is_impactable(int x, int y);

  void tick();
  void remove_item(int x, int y);
  void execute_intentions(std::vector<char> & intentions, int & client_id);

  friend class GamePlay;
  
};

#endif // __SERVER_MAP_H__
