#ifndef YDOORTILE_H
#define YDOORTILE_H

#include "DoorTile.h"
class YDoorTile: public DoorTile {
  public:
    explicit YDoorTile(const SDL_Rect* clip):
      DoorTile::DoorTile(clip) {}
    ~YDoorTile() {}
};

#endif  // YDOORTILE_H
