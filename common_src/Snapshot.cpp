#include "Snapshot.h"
Snapshot::Snapshot(){}

Snapshot::~Snapshot(){
    for (auto &object : this->objects){ 
        delete object;
    }
    for (auto &action : this->actions){ 
        delete action;
    }
    for (auto &player : this->players){ 
        delete player;
    }
}


/**************SETTERS*******************/
void Snapshot::add_action(Action *action){
    this->actions.push_back(action);
}
void Snapshot::add_object(object_t* object){
    this->objects.push_back(object);
}
void Snapshot::add_player(player_t *player){
    this->players.push_back(player);
}
/***************************************/



/**************GETTERS*******************/
object_t* Snapshot::get_object(int & id){
    for (auto &object : this->objects){ 
        if (object->id == id){
            return object;
        }
    }
    object_t *object = new object_t;
    object->id = id;
    this->objects.push_back(object);
    return object;
}
Action* Snapshot::get_action(int & id){
    for (auto &action : this->actions){ 
        if (action->get_id() == id){
            return action;
        }
    }
    Action* action = new Action(id);
    this->actions.push_back(action);
    return action;
}
player_t* Snapshot::get_player(int & id){
    for (auto &player : this->players){ 
        if (player->player_id == id){
            return player;
        }
    }
    player_t* player = new player_t;
    player->player_id = id;
    this->players.push_back(player);
    return player;
}
/***************************************/
