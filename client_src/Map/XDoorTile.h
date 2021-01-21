#ifndef XDOORTILE_H
#define XDOORTILE_H

#include "DoorTile.h"
class XDoorTile: public DoorTile {
  public:
    explicit XDoorTile(const SDL_Rect* clip):
      DoorTile::DoorTile(clip) {};
    ~XDoorTile() {}
};

#endif  // XDOORTILE_H
