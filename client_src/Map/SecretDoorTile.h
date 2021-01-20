#ifndef SECRETDOORTILE_H
#define SECRETDOORTILE_H

#include "Tile.h"
class SecretDoorTile: public Tile {
  const double OPENING_SPEED = 0.05;
  bool isClosed;
  double depth_percentage;

  public:
    explicit SecretDoorTile(const SDL_Rect* clip);
    ~SecretDoorTile();
    double getDepthPercentage() const;
    void setClosed(bool isClosed);
    void actualizar() override;
};

#endif  // SECRETDOORTILE_H
