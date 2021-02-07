#ifndef YDOORTILE_H
#define YDOORTILE_H

#include "DoorTile.h"
class YDoorTile: public DoorTile {
  public:
    explicit YDoorTile(const SDL_Rect* clip, int x, int y, Player& player, ResourcesLoader& src):
      DoorTile::DoorTile(clip, x, y, player, src) {}
    ~YDoorTile() {}
};

#endif  // YDOORTILE_H
