#include "Action.h"
#include <iostream>

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
    std::cout << "TRUE" <<std::endl;

}

int Action::get_id(){
    return this->player_id;
}

// Action::Action(Action&& other){
//     this->player_id = other.player_id;
//     this->impact_y = other.impact_y;
//     this->impact_x = other.impact_x;
//     this->weapon_id = other.weapon_id;
//     this->state = true;
// }

// Action& Action::operator=(Action&& other) {
//     this->player_id = other.player_id;
//     this->impact_y = other.impact_y;
//     this->impact_x = other.impact_x;
//     this->weapon_id = other.weapon_id;
//     this->state = true;
//     return *this;
// }


bool Action::active(){
    return this->state;
}



