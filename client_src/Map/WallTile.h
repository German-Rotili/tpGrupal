#ifndef WALLTILE_H
#define WALLTILE_H

#include "Tile.h"
class WallTile : public Tile {
  public:
    explicit WallTile(const SDL_Rect* clip):
      Tile::Tile(clip) {}
    ~WallTile() {}
    void update() override {}
};

#endif  // WALLTILE_H
