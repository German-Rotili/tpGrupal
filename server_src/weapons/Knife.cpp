#include "Knife.h"
#include "Weapon.h"
#include "../Config.h"
#include "../Constants.h"
#include "../Map.h"
#include "../Player.h"

Knife::Knife(Map &map, Config &config) {
  this->map = map;
}

void Knife::attack() {
  // de los jugadores que esten a distancia, y ademas en un angulo aceptable,
  // acuchilla al que este mas cerca.
  if (!this->is_in_cooldown()) {
    Player *closest_player = nullptr;
    float min_distance = 0;
    for (Player &player : this->map.get_players()) {
      float pos_x = player.get_pos_x();
      float pos_y = player.get_pos_y();

      float distance = this->inventory.get_player().get_distance(pos_x, pos_y);

      if (distance < this->range &&
          this->inventory.get_player().get_angle_difference(pos_x, pos_y)) {
        // si esta a rango y en un angulo tolerable.
        if (distance < min_distance) {
          closest_player = &player;
        }
      }
    }
    if (closest_player != nullptr) {
      closest_player->get_damaged(this->damage);
      this->last_shot_timer.start();
    }
  }
}
