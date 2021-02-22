#include "Position.h"
#include <cmath>
#include <math.h>
#include "Map.h"
#include "ServerConfigHandler.h"
#include "Constants.h"
#include <iostream>

void Position::update(char mov) {
  // std::cout << " pos x: " << this->x << " pos y : " << this->y << std::endl;

  if (mov == FORWARD || mov == BACKWARDS) {
    float offset_x = this->get_x_offset(mov);
    float offset_y = this->get_y_offset(mov);

    //std::cout << " offset x: " << offset_x << " offset y : " << offset_y << std::endl;

    
    int new_x = (int)(this->x + offset_x);
    int new_y = (int)this->y;

    int hitbox_limit_x = (offset_x > 0) ? this->x + offset_x + this->hitbox_radius
                                        : this->x + offset_x - this->hitbox_radius;

    if (this->map->valid_position(hitbox_limit_x, new_y)) {
      this->x += offset_x;
    } else { // si se choca contra una pared muevo el personaje para que la
             // hitbox este justo al limite.
      this->x = (offset_x > 0) ? hitbox_limit_x - this->hitbox_radius
                                  : hitbox_limit_x + 1 + this->hitbox_radius ;
      // std::cout << "compenso por pared";
    }
    new_x = (int)(this->x);
    new_y = (int)(this->y + offset_y);

    int hitbox_limit_y = (offset_y > 0) ? this->y + offset_y + this->hitbox_radius
                                        : this->y + offset_y - this->hitbox_radius;
    // std::cout << " verificando pos x: " << new_x << " pos y : " << hitbox_limit_y << std::endl;
    if (this->map->valid_position(new_x, hitbox_limit_y)) {
      this->y += offset_y;
    } else { // si se choca contra una pared muevo el personaje para que la
             // hitbox este justo al limite.
      this->y = (offset_y > 0) ? hitbox_limit_y - this->hitbox_radius
                                  : hitbox_limit_y + 1 + this->hitbox_radius;
      //  std::cout << "compenso por pared";

    }
  } else {

    this->update_angle(mov);
  }

}

float Position::get_pos_x() { return this->x; }

float Position::get_pos_y() { return this->y; }

float Position::get_hitbox_radius() { return this->hitbox_radius; }

float Position::get_angle() { return this->angle; }

void Position::set_position(int x, int y) {
  // std::cout << "set position en  " << x << " " << y << std::endl;
  this->x = (float)x;
  this->y = (float)y;
}

int Position::colides(Position &) { return 1; }

float Position::get_distance(float x, float y) {
  return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
}

float Position::get_distance(Position &position) {
  return this->get_distance(position.get_pos_x(), position.get_pos_y());
}

bool Position::is_in_hitbox(float x, float y) {
  return (abs(x - this->x) <= this->hitbox_radius ||
          abs(y - this->y) <= this->hitbox_radius);
}

float Position::get_angle_difference(Position position) {
  return this->get_angle_difference(position.get_pos_x(), position.get_pos_y());
}

float Position::get_angle_difference(float x, float y) { // devuelve en radianes
  float dot = (x * this->x) + (y * this->y);
  float mod_this = sqrt(pow(this->x, 2) + pow(this->y, 2));
  float mod_other = sqrt(pow(x, 2) + pow(y, 2));
  return abs(acos(dot / (mod_other * mod_this)));
}

float Position::get_y_offset(char intention) {
  if (intention == FORWARD) {
    return this->linear_vel * sin(this->angle * PI / 180);
  } else if (intention == BACKWARDS) {
    return -this->linear_vel * sin(this->angle * PI / 180);
  } else {
    return 0;
  }
}

float Position::get_x_offset(char intention) {
  if (intention == FORWARD) {
    return this->linear_vel * cos(this->angle * PI / 180);
  } else if (intention == BACKWARDS) {
    return -this->linear_vel * cos(this->angle * PI / 180);
  } else {
    return 0;
  }
}

void Position::update_angle(char intention) {
  if (intention == RIGHT) {
    this->angle += this->angular_vel;
  }
  if (intention == LEFT) {
    this->angle -= this->angular_vel;
  }

  // no es necesario esto realmente. pero me gustaria que se mantenga el angulo
  // entre 0 y 360. quizas en una hora de juego hacemos un overflow sino.
  this->angle = (this->angle < 0) ? 360 + this->angle : this->angle;
  this->angle = (this->angle > 360) ? this->angle - 360 : this->angle;
}

Position::Position(Map *map, ServerConfigHandler *config) 
{
  this->map = map;
  this->config = config;
  this->angle = 30;
  actorStats_t stats = this->config->getPlayerStats();
  this->hitbox_radius = stats.hitbox_radius;
  this->linear_vel = stats.linear_vel;
  this->angular_vel = stats.angular_vel;
}
