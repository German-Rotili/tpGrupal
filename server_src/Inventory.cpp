#include "Inventory.h"
#include "../weapons/Pistol.h"
#include <memory>

Player &Inventory::get_player() { return *this->player; }

void Inventory::attack() { this->weapons[current_weapon]->attack(); }

int Inventory::get_ammo() { return this->ammo; }

void Inventory::spend_ammo(int ammo_spent) { this->ammo -= ammo_spent; }

char Inventory::get_current_weapon_id() { return this->current_weapon; }

Inventory::Inventory(Player &player, Map &Map) {
  this->player = &player;
  this->map = map;
  this->weapons[PISTOL] = std::make_unique<Pistol>(this->map, this->config);
  // this->ammo = Config.initialammo;
}


