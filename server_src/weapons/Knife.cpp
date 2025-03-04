#include "Knife.h"
#include "Weapon.h"
#include "../ServerConfigHandler.h"
#include "../Constants.h"
#include "../Map.h"
#include "../Player.h"
#include <iostream>
Knife::Knife(Map *map, ServerConfigHandler *config, Inventory *inventory) : Weapon{map, config, inventory} {
  this->map = map;
  weaponStats_t stats = this->config->getWeaponStats(KNFIE);
  this->max_damage = stats.max_damage;
  this->max_spread = stats.max_spread;
  this->ammo_cost = stats.ammo_cost;
  this->cooldown = stats.cooldown;
  this->stability_reset = stats.stability_reset;
  this->max_acurate_range = stats.max_acurate_range;
}

void Knife::attack() {
  // de los jugadores que esten a distancia, y ademas en un angulo aceptable,
  // acuchilla al que este mas cerca.
  if (!this->is_in_cooldown()) {
    Player *closest_player = nullptr;
    float min_distance = 0;
    this->map->add_action(this->inventory->get_player()->get_id(), this->inventory->get_current_weapon_id(), 0,0);
    for (Player *player : this->map->get_players()) {
      if(player == this->inventory->get_player()) continue;
      float pos_x = player->get_pos_x();
      float pos_y = player->get_pos_y();

      float distance = this->inventory->get_player()->get_distance(pos_x, pos_y);

      if (distance < this->range &&
          this->inventory->get_player()->get_angle_difference(pos_x, pos_y) <= 50) {
            // std::cout << "hay un player que la comio" << std::endl;
        if (min_distance == 0 || distance < min_distance) {
          closest_player = player;
        }
      }
    }
    if (closest_player != nullptr) {
      closest_player->get_damaged(this->damage);
    }
    this->last_shot_timer.start();
  }
}
