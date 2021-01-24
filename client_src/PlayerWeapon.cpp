#include "PlayerWeapon.h"
PlayerWeapon::PlayerWeapon(bool obtenida):
  disponible(obtenida){}

PlayerWeapon::~PlayerWeapon() {}

bool PlayerWeapon::estaDisponible() const {
  return this->disponible;
}
