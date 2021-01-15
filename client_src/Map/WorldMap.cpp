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
        if ((*col) == 0) {
          map[irow].push_back(NULL);
        } else if (*col == 1) {
          map[irow].push_back(new WallTile(&WALL_CLIP));
        } else if (*col == 3) {
          map[irow].push_back(new XDoorTile(&DOOR_CLIP));
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

void WorldMap::actualizar() {
  std::vector<Tile*>::iterator tile;
  for (tile = actualizables.begin(); tile != actualizables.end(); tile++) {
    (*tile)->actualizar();
  }
}
