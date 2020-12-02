#include "server_player.h"
#include <iostream>

Player::Player(int & pos_x, int & pos_y, std::string & 
    orientation): pos_x(pos_x), pos_y(pos_y), orientation(orientation){}

Player::~Player(){}

int Player::get_pos_x(){
    return this->pos_x;
}
int Player::get_pos_y(){
    return this->pos_y;
}

void Player::update_position(int & pos_x, int & pos_y, std::string dir){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->orientation = dir;
}
