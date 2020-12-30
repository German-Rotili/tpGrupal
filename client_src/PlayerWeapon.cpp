#include "PlayerWeapon.h"
PlayerWeapon::PlayerWeapon(bool obtenida, int balasIniciales):
  obtenida(obtenida),
  cantBalas(balasIniciales) {}

PlayerWeapon::~PlayerWeapon() {}

int PlayerWeapon::getCantBalas() {
  return cantBalas;
}

void PlayerWeapon::setCantBalas(int balasActuales) {
  cantBalas = balasActuales;
}

bool PlayerWeapon::estaEnInventario() {
  return this->obtenida;
}
