#include "Rocket.h"
#include "../Map.h"
#include "../ServerConfigHandler.h"
#include "../Constants.h"
#include <algorithm>
#include <math.h>

#include "../Player.h"

Rocket::Rocket(Map * map, ServerConfigHandler *config, Player *player, float pos_x, float pos_y,
               float direction){
  this->y_pos = pos_y;
  this->x_pos = pos_x;
  this->direction = direction;
  this->map = map;
  this->config = config;
  this->player = player;
}
 //fix self explode.
void Rocket::update_position() {
  this->x_pos += get_x_offset();
  this->y_pos += get_y_offset();
}


bool Rocket::tick() {
  this->update_position();
  if (!this->map->valid_position(this->x_pos, this->y_pos)) {
    this->explode();
    return true;
  }
  if(this->colides_with_player()){
    return true;
  }
  return false;
  
}


void Rocket::explode() {
  for (Player *player : this->map->get_players()) {
    if(this->player->get_id() != player->get_id()){
      float distance = player->get_distance(this->x_pos, this->y_pos);
      if (distance <= this->explotion_radius) {
        player->get_damaged(this->damage * (this->explotion_radius) /
                          std::min(this->explotion_radius, distance));
      }
    }
    this->map->add_action(-1, 0, this->x_pos, this->y_pos);
  }
}
float Rocket::get_pos_y() {
  return this->y_pos;
}
float Rocket::get_pos_x() {
  return this->x_pos;
}

float Rocket::get_y_offset() {
  return this->velocity * sin(this->direction * PI / 180);
}
float Rocket::get_x_offset() {
  return this->velocity * cos(this->direction * PI / 180);
}

bool Rocket::colides_with_player() {
    for (Player *player : this->map->get_players()) {
        if(player->is_in_hitbox(this->x_pos, this->y_pos) && player->get_id() != this->player->get_id()){
            this->explode();
            return true;
        }
    }
    return false;
    // avisar al action helper que exploto y donde.
}