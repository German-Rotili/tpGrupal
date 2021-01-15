#include "DoorTile.h"

DoorTile::DoorTile(const SDL_Rect* clip):
      Tile::Tile(clip),
      isOpened(false),
      closed_percentage(0.5) {}

DoorTile::~DoorTile() {}

void DoorTile::setOpened(bool isOpened) {
  // Si hubo un cambio puedo reproducir un sonido.
  this->isOpened = isOpened;
}

void DoorTile::actualizar() {
  if (isOpened && (closed_percentage > 0)) {
    closed_percentage -= OPENING_SPEED;
  }
  else if (!isOpened && (closed_percentage < 1)) {
    closed_percentage += OPENING_SPEED;
  }
}

double DoorTile::getClosedPercentage() const {
  return this->closed_percentage;
}
