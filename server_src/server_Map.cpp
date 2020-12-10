#include "server_Map.h"
#include <iostream>

Map::Map(int x, int y):x(x),y(y){}

bool Map::valid_position(int & pos_x, int & pos_y){
    
    if (pos_x > this->x || pos_y > this->y || pos_x < 0 || pos_y < 0){
        return false;
    }

    // std::vector<Player&> ::iterator it = this->players.begin();

    // for (; it != this->players.end(); ++it){
    //     if ((it)->get_pos_x() == x || (it)->get_pos_y() == y){
    //         return false;
    //     }
    // }
    return false;
}
// tenemos que ver si el movimiento realmente va a ser asi. yo creo que el movimiento es un poco mas fluido dentro del casillero. hay que preguntar a los de vision
void Map::move_player(Player & player, std::string direction){
    int aux_x = player.get_pos_x();
    int aux_y = player.get_pos_y();

    if (direction == UP){
        aux_y += 1;
    } else if (direction == DOWN){
        aux_y -= 1;
    } else if (direction == LEFT) {
        aux_x -= 1;
    } else if (direction == RIGHT){
        aux_x += 1;
    }
    
    std::cout << aux_x << std::endl;
    std::cout << aux_y << std::endl;

    if (valid_position(aux_x, aux_y)){
        player.update_position(aux_x, aux_y, direction);
    }
}

void Map::add_player(Player & player){
    // this->players.push_back(player);
}



Map::~Map(){}
