#ifndef DOORTILE_H
#define DOORTILE_H

#include "../ResourcesLoader.h"
#include "../SDLWrappers/SdlSound.h"
#include "../Player.h"
#include "Tile.h"
class DoorTile: public Tile {
  const double OPENING_SPEED = 0.05;
  bool isClosed;
  double closed_percentage;

  int x;
  int y;

  // Guardo referencia a player para saber su posicion a la hora de reproducir sonido
  const Player& player;

  SdlSound& snd_open;
  SdlSound& snd_close;

  public:
    const double door_depth = 0.5;
    DoorTile(const SDL_Rect* clip, int x, int y, Player& player, ResourcesLoader& src);
    ~DoorTile();
    double getClosedPercentage() const;
    void setClosed(bool isClosed);
    void actualizar() override;
};

#endif  // DOORTILE_H
