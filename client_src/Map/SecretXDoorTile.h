#ifndef SECRETXDOORTILE_H
#define SECRETXDOORTILE_H

#include "SecretDoorTile.h"
class SecretXDoorTile: public SecretDoorTile {
  public:
    explicit SecretXDoorTile(const SDL_Rect* clip):
      SecretDoorTile::SecretDoorTile(clip) {}
    ~SecretXDoorTile() {}
};

#endif  // SECRETXDOORTILE_H
