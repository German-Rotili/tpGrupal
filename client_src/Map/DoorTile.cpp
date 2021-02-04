#include "DoorTile.h"

DoorTile::DoorTile(const SDL_Rect* clip):
      Tile::Tile(clip),
      isClosed(true),
      closed_percentage(0.5) {}

DoorTile::~DoorTile() {}

void DoorTile::setClosed(bool isClosed) {
  // Si hubo un cambio puedo reproducir un sonido.
  this->isClosed = isClosed;
}

void DoorTile::actualizar() {
  if (isClosed && (closed_percentage > 0.001)) {
    closed_percentage -= OPENING_SPEED;
  } else if (!isClosed && (closed_percentage < 1)) {
    closed_percentage += OPENING_SPEED;
  }
}

double DoorTile::getClosedPercentage() const {
  return this->closed_percentage;
}
