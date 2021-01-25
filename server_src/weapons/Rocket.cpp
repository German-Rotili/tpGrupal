#include "Rocket.h"
#include "../Constants.h"
#include <math.h>
#include <algorithm>

Rocket::Rocket(Map map, Config config, float pos_x, float pos_y, float direction){
    this->y_pos = pos_y;
    this->x_pos = pos_x;
    this->direction = direction;
}


void Rocket::update_position(){
    this->x_pos += get_x_offset();
    this->y_pos += get_y_offset();
}


bool Rocket::tick() {
    this->update_position();

    if(!this->map.valid_position(this->x_pos, this->y_pos)){
        this->explode();
    }
}


float Rocket::get_y_offset(){
    return this->velocity * sin(this->direction * PI/180);
}

float Rocket::get_x_offset(){

    return this->velocity * cos(this->direction * PI/180);

}
void Rocket::explode() {
    for(Player &player : this->map.get_players()){
        float distance = player.get_distance(this->x_pos, this->y_pos); 
        if(distance <= this->explotion_radius){
            player.get_damaged(this->damage * (this->explotion_radius) / std::min(this->explotion_radius, distance));
    }
    //avisar al action helper que exploto y donde.
}
