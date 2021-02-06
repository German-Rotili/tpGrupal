#ifndef XDOORTILE_H
#define XDOORTILE_H

#include "DoorTile.h"

class XDoorTile: public DoorTile {
  public:
    explicit XDoorTile(const SDL_Rect* clip, int x, int y, Player& player, ResourcesLoader& rc):
      DoorTile::DoorTile(clip, x, y, player, rc) {};
    ~XDoorTile() {}
};

#endif  // XDOORTILE_H
