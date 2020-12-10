#ifndef MAP_H
#define MAP_H
#include <vector>
#include "server_player.h"
#define UP "u"
#define DOWN "d"
#define LEFT "l"
#define RIGHT "r"

//para ver si una posicion es valida el mapa solo sabe si esta ocupada por un objeto. no por jugadores. esto va por logica de hitbox aparte. 

class Map{
private:
   // std::vector <Player&> players;
    int x; //map boundary width
    int y; //map boundary height

public:
    Map(int x, int y);
    ~Map();
    bool valid_position(int & pos_x, int & pos_y);
    void add_player(Player & player);
    void move_player(Player & player, std::string direction);
    void get_players(); // placeholder
};
#endif
