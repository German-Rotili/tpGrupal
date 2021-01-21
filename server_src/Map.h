#ifndef __SERVER_MAP_H__
#define __SERVER_MAP_H__
#include <vector>
#include "Player.h"
#include "Constants.h"

//para ver si una posicion es valida el mapa solo sabe si esta ocupada por un objeto. no por jugadores. esto va por logica de hitbox aparte. 

class Map{
private:
    std::vector <Player&> players;
    int x; //map boundary width
    int y; //map boundary height
    int map_vector[7][10] = {{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                       {3, 0, 0, 0, 0, 5, 5, 0, 0, 1},
                       {3, 0, 0, 0, 0, 5, 5, 0, 0, 3},
                       {3, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                       {3, 0, 0, 0, 0, 0, 0, 0, 0, 3},
                       {3, 0, 0, 0, 0, 5, 5, 0, 0, 1},
                       {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                    };
public:
    Map();
    ~Map();
    bool valid_position(int & pos_x, int & pos_y);
    // void add_player(Player & player);
    // void move_player(Player & player, std::string direction);
    std::vector <Player&> get_players(); // placeholder
    std::pair<float, float> get_impact_point(const Player &player);
    bool is_impactable(int x, int y);
};



#endif // __SERVER_MAP_H__