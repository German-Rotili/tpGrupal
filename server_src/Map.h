#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <map>
#include "./weapons/Rocket.h"
#include "ServerConfigHandler.h"
#include "../common_src/Action.h"
#include "Player.h"
#include "Door.h"
#include "../common_src/Timer.h"

class Action;
class Door;
class Player;
class Rocket;
class GamePlay;
class Map {
private:
  std::vector<Player*> players;
  std::vector<Rocket*> rockets;
  std::vector<Action> actions;
  std::vector<std::vector<int>> map;
  std::vector<char> raw_map;
  std::map<int, std::map<int, Door>> doors;
  std::map<int, std::map<int, char>> items;
  Timer game_timer;
  int game_time_limit = 30000;
  ServerConfigHandler config;


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
  void add_player(int id,std::vector<char> username);   
  std::vector<Player*> &get_players(); // placeholder
  std::map<int, std::map<int, Door>> &get_doors();

  void start();
  void add_rocket(float posx, float posy, float direction, Player *);
  bool is_item(char id);

  bool valid_position(int x, int y);
  bool is_impactable(int x, int y);

  void tick();
  void remove_item(int x, int y);
  void execute_intentions(std::vector<char> intentions, int client_id);

  std::vector<char> get_raw_map();

  void add_action(int player_id, float weapon_id, float posx, float posy);
  void add_item(int id, int x, int y);

  bool is_game_over();



  friend class GamePlay;
};


#endif // __MAP_H__