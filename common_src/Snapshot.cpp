#include "Snapshot.h"
Snapshot::Snapshot(){}

Snapshot::~Snapshot(){
    // for (object_t *object : this->objects){ 
    //     delete object;
    // }
    // for (Action *action : this->actions){ 
    //     delete action;
    // }
    // for (player_t *player : this->players){ 
    //     delete player;
    // }
}

void Snapshot::print(){
    for (auto &player : this->players){ 
    std::cout << "/********PLAYER*********/"<<std::endl;
    std::cout << player.player_id <<std::endl;
    std::cout << player.pos_x <<std::endl;
    std::cout << player.pos_y <<std::endl;
    std::cout << player.direction <<std::endl;
    std::cout << player.ammo <<std::endl;
    std::cout << player.current_weapon <<std::endl;
    std::cout << "/**********************/"<<std::endl;    
    }
}



/**************SETTERS*******************/
void Snapshot::add_action(Action action){
    this->actions.push_back(action);
}
void Snapshot::add_object(object_t object){
    this->objects.push_back(object);
}
void Snapshot::add_player(player_t player){
    this->players.push_back(player);
}
/***************************************/



/**************GETTERS*******************/
object_t Snapshot::get_object(int & id){
    for (auto &object : this->objects){ 
        if (object.id == id){
            return object;
        }
    }
    object_t object;
    object.id = id;
    this->objects.push_back(object);
    return object;
}
Action Snapshot::get_action(int & id){
    for (auto &action : this->actions){ 
        if (action.get_id() == id){
            return action;
        }
    }
    Action action(id);
    this->actions.push_back(action);
    return action;
}
player_t Snapshot::get_player(int & id){
    for (auto &player : this->players){ 
        if (player.player_id == id){
            return player;
        }
    }
    player_t player;
    player.player_id = id;
    this->players.push_back(player);
    return player;
}
/***************************************/
