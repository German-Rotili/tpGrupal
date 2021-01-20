#ifndef SECRETYDOORTILE_H
#define SECRETYDOORTILE_H

#include "SecretDoorTile.h"
class SecretYDoorTile: public SecretDoorTile {
  public:
    explicit SecretYDoorTile(const SDL_Rect* clip):
      SecretDoorTile::SecretDoorTile(clip) {}
    ~SecretYDoorTile() {}
};

#endif  // SECRETYDOORTILE_H
