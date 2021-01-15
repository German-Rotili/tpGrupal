#ifndef DOORTILE_H
#define DOORTILE_H

#include "Tile.h"
class DoorTile: public Tile {
  const double OPENING_SPEED = 0.05;
  bool isOpened;
  double closed_percentage;

  public:
    const double door_depth = 0.5;
    explicit DoorTile(const SDL_Rect* clip);
    ~DoorTile();
    double getClosedPercentage() const;
    void setOpened(bool isOpened);
    void actualizar() override;
};

#endif  // DOORTILE_H
