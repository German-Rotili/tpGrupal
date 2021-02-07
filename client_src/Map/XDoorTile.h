#ifndef XDOORTILE_H
#define XDOORTILE_H

#include "DoorTile.h"

class XDoorTile: public DoorTile {
  public:
    explicit XDoorTile(const SDL_Rect* clip, int x, int y, Player& player, ResourcesLoader& src):
      DoorTile::DoorTile(clip, x, y, player, src) {};
    ~XDoorTile() {}
};

#endif  // XDOORTILE_H
