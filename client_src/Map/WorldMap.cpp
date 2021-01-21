#include "WorldMap.h"

WorldMap::WorldMap(std::vector<std::vector<int>>& rawMap) {
  int irow = 0;
  std::vector<std::vector<int>>::iterator row;
  std::vector<int>::iterator col;
  for (row = rawMap.begin(); row != rawMap.end(); row++) {
    int icol = 0;
    std::vector<Tile*> v;
    map.push_back(v);
    for (col = row->begin(); col != row->end(); col++) {
        if ((*col) == 21) {
          map[irow].push_back(NULL);
        } else if (*col == 23) {
          map[irow].push_back(new YDoorTile(&DOOR_CLIP));
          actualizables.push_back(map[irow].back());
        } else if (*col == 24) {
          map[irow].push_back(new XDoorTile(&DOOR_CLIP));
          actualizables.push_back(map[irow].back());
        } else if (*col == 25) {
          map[irow].push_back(new SecretYDoorTile(&WALL_CLIP));
          actualizables.push_back(map[irow].back());
        } else if (*col == 26) {
          map[irow].push_back(new SecretXDoorTile(&WALL_CLIP));
          actualizables.push_back(map[irow].back());
        } else {
          map[irow].push_back(new WallTile(&WALL_CLIP));
          actualizables.push_back(map[irow].back());
        }
      icol++;
    }
    this->xsize = icol;
    irow++;
  }
  this->ysize = irow;
}
WorldMap::~WorldMap() {
  std::vector<std::vector<Tile*>>::iterator row;
  std::vector<Tile*>::iterator col;
  for (row = map.begin(); row != map.end(); row++) {
    for (col = row->begin(); col != row->end(); col++) {
      delete *col;
    }
  }
}

const Tile* WorldMap::getTile(int x, int y) {
  if (x < 0 || x >= xsize || y < 0 || y >= ysize) return NULL;
  return map[y][x];
}

// Combinar estas 2 funciones para mejor performance?
void WorldMap::setDoorsClosed(bool doorClosed) {
  for (auto tile = actualizables.begin(); tile != actualizables.end(); tile++) {
    if (DoorTile* door = dynamic_cast<DoorTile*> (*tile))
      (door)->setClosed(doorClosed);
    else if (SecretDoorTile* door = dynamic_cast<SecretDoorTile*> (*tile))
      (door)->setClosed(doorClosed);
  }
}

void WorldMap::actualizar() {
  for (auto tile = actualizables.begin(); tile != actualizables.end(); tile++) {
    (*tile)->actualizar();
  }
}
