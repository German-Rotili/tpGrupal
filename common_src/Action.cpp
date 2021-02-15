#include "Action.h"

Action::Action(int id):player_id(id),state(false){}

Action::~Action(){}

void Action::update_state(bool new_state){
    this->state = new_state;
}

void Action::update_values(double impact_x, double impact_y, char weapon_id){
    this->impact_y = impact_y;
    this->impact_x = impact_x;
    this->weapon_id = weapon_id;
    this->state = true;

}

int Action::get_id(){
    return this->player_id;
}

bool Action::active(){
    return this->state;
}



