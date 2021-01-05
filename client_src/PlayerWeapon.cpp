#include "PlayerWeapon.h"
PlayerWeapon::PlayerWeapon(bool obtenida, int balasIniciales):
  disponible(obtenida),
  cantBalas(balasIniciales) {}

PlayerWeapon::~PlayerWeapon() {}

void PlayerWeapon::setCantBalas(int balasActuales) {
  cantBalas = balasActuales;
}

int PlayerWeapon::getCantBalas() const {
  return this->cantBalas;
}

bool PlayerWeapon::estaDisponible() const {
  return this->disponible;
}
