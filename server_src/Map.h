#ifndef __SERVER_MAP_H__
#define __SERVER_MAP_H__
#include "./weapons/Rocket.h"
#include "Constants.h"
#include "Player.h"
#include <vector>

// para ver si una posicion es valida el mapa solo sabe si esta ocupada por un
// objeto. no por jugadores. esto va por logica de hitbox aparte.

class Map {
private:
  std::vector<Player &> players;
  std::vector<std::vector<int>> map;
  std::vector<Rocket> rockets;

public:
  Map();
  ~Map();

  void add_player(Player &player);     // ver quien hace los players
  std::vector<Player &> get_players(); // placeholder
  void add_rocket(Rocket Rocket);

  bool valid_position(int pos_x, int pos_y);
  bool is_impactable(int x, int y);

  void tick();
  void execute_intentions();
};

#endif // __SERVER_MAP_H__