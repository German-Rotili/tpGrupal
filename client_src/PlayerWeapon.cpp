#include "PlayerWeapon.h"
PlayerWeapon::PlayerWeapon(bool obtenida, SdlSound& sonido1, SdlSound& sonido2):
  disponible(obtenida),
  sonido1(sonido1),
  sonido2(sonido2) {}

PlayerWeapon::~PlayerWeapon() {}

bool PlayerWeapon::estaDisponible() const {
  return this->disponible;
}

void PlayerWeapon::reproducirSonido() const {
  if (rand() % 2){
    sonido1.play(-1, 0);
  } else {
    sonido2.play(-1, 0);
  }
}

void PlayerWeapon::setDisponible(bool disponible) {
  this->disponible = disponible;
}
