#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <vector>
#include "../SDLWrappers/SdlTexture.h"
#include "../SDLWrappers/SdlRenderer.h"
#include "../ClientSettings.h"
#include "Tile.h"
#include "WallTile.h"
#include "XDoorTile.h"
#include "YDoorTile.h"
#include "SecretXDoorTile.h"
#include "SecretYDoorTile.h"


class WorldMap {
  std::vector<std::vector<class Tile*>> map;
  int xsize;
  int ysize;
  std::vector<class Tile*> actualizables;

  const SDL_Rect WALL_CLIP = {0, 0, 64, 64};
  const SDL_Rect DOOR_CLIP = {64, 11*64, 64, 64};

  public:
    explicit WorldMap(std::vector<std::vector<int>> & rawMap);
    ~WorldMap();
    const class Tile* getTile(int x, int y);
    void setDoorsClosed(bool doorClosed);
    void actualizar();
};

#endif  // WORLDMAP_H
