#ifndef YDOORTILE_H
#define YDOORTILE_H

#include "DoorTile.h"
class YDoorTile: public DoorTile {
  public:
    explicit YDoorTile(const SDL_Rect* clip, int x, int y, Player& player, ResourcesLoader& rc):
      DoorTile::DoorTile(clip, x, y, player, rc) {}
    ~YDoorTile() {}
};

#endif  // YDOORTILE_H
