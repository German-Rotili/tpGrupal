#include "WorldMap.h"
#include <iostream>

WorldMap::WorldMap(std::vector<std::vector<int>> & rawMap) {
  // Creacion de clips para las paredes.
  for (int i = 0; i < CANT_WALLS; i++) {
    int row = i / 3;
    int column =  (i % 3);
    wallClips[i] = {column * 64, row * 64, 64, 64};;
  }

  int irow = 0;
  std::vector<std::vector<int>>::iterator row;
  std::vector<int>::iterator col;
  for (row = rawMap.begin(); row != rawMap.end(); row++) {
    int icol = 0;
    std::vector<Tile*> v;
    map.push_back(v);
    for (col = row->begin(); col != row->end(); col++) {
      if ((*col) >= 0 && (*col) <= 33) {  // Pared
        map[irow].push_back(new WallTile(&(wallClips[*col])));
        actualizables.push_back(map[irow].back());
      } else if (*col == 34) {  // Puerta comun
        map[irow].push_back(new YDoorTile(&DOOR_CLIP));
        actualizables.push_back(map[irow].back());
      } else if (*col == 35) {
        map[irow].push_back(new XDoorTile(&DOOR_CLIP));
        actualizables.push_back(map[irow].back());
      } else if (*col == 59) {  // Puerta con llave 1
        map[irow].push_back(new YDoorTile(&KEYDOOR_CLIP));
        actualizables.push_back(map[irow].back());
      } else if (*col == 60) {
        map[irow].push_back(new XDoorTile(&KEYDOOR_CLIP));
        actualizables.push_back(map[irow].back());
      } else if (*col == 61) {  // Puerta con llave 2 (puedo unificar con la 1)
        map[irow].push_back(new YDoorTile(&KEYDOOR_CLIP));
        actualizables.push_back(map[irow].back());
      } else if (*col == 62) {
        map[irow].push_back(new XDoorTile(&KEYDOOR_CLIP));
        actualizables.push_back(map[irow].back());
      } else if (*col == 63) {  // Puerta secreta
        //Obtener direccion de clip del tile en x-1
        map[irow].push_back(new SecretYDoorTile(&WALL_CLIP));
        actualizables.push_back(map[irow].back());
      } else if (*col == 64) {
        //Obtener direccion de clip del tile en y-1
        map[irow].push_back(new SecretXDoorTile(&WALL_CLIP));
        actualizables.push_back(map[irow].back());
      } else {
        map[irow].push_back(NULL);
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
