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

  // 0 a 33: Distintos tipos de paredes
  // 34 = PUERTA HORIZONTAL
  // 35 = PUERTA VERTICAL
  // 36 = BARRIL
  // 37 = POZO
  // 38 = COLUMNA
  // 39 = ESTATUA
  // 40 = LAMPARA1
  // 41 = LAMPARA2
  // 42 = CHARCO
  // 43 = HUESOS
  // 44 = LLAVE1
  // 45 = LLAVE2
  // 46 = SANGRE
  // 47 = COMIDA
  // 48 = KIT
  // 49 = BALAS
  // 50 = AMETRALLADORA
  // 51 = CANIONDECADENA
  // 52 = LANZACOHETES
  // 53 = CRUZ
  // 54 = COPA
  // 55 = COFRE
  // 56 = CORONA
  // 57 = VACIO
  // 58 = SPAWN
  // Las puertas para llaves son 59, 60 y 61, 62
  // Las secretas son 63 y 64
  // Siempre primero la horiontal y despues la vertical

  static const int CANT_WALLS = 34;
  SDL_Rect wallClips[CANT_WALLS];
  const SDL_Rect DOOR_CLIP = {64, 11*64, 64, 64};
  const SDL_Rect KEYDOOR_CLIP = {128, 11*64, 64, 64};

  public:
    explicit WorldMap(std::vector<std::vector<int>> & rawMap);
    ~WorldMap();
    const class Tile* getTile(int x, int y);
    void setDoorsClosed(bool doorClosed);
    void actualizar();
};

#endif  // WORLDMAP_H
