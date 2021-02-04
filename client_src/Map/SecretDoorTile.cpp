#include "SecretDoorTile.h"

SecretDoorTile::SecretDoorTile(const SDL_Rect* clip):
      Tile::Tile(clip),
      isClosed(true),
      depth_percentage(0) {}

SecretDoorTile::~SecretDoorTile() {}

void SecretDoorTile::setClosed(bool isClosed) {
  // Si hubo un cambio puedo reproducir un sonido.
  this->isClosed = isClosed;
}

void SecretDoorTile::actualizar() {
  if (isClosed && (depth_percentage > 0.001)) {
    depth_percentage -= OPENING_SPEED;
  } else if (!isClosed && (depth_percentage < 1)) {
    depth_percentage += OPENING_SPEED;
  }
}

double SecretDoorTile::getDepthPercentage() const {
  return this->depth_percentage;
}
