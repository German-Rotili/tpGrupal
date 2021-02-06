#include <cmath>
#include "DoorTile.h"

DoorTile::DoorTile(const SDL_Rect* clip, int x, int y, Player& player, ResourcesLoader& rc):
      Tile::Tile(clip),
      x(x),
      y(y),
      isClosed(true),
      closed_percentage(0.5),
      player(player),
      snd_open(rc.snd_door_open),
      snd_close(rc.snd_door_closed) {}

DoorTile::~DoorTile() {}

void DoorTile::setClosed(bool isClosed) {
  // Si hubo un cambio puedo reproducir un sonido.
  if (this->isClosed & !isClosed) {
    // Sonido de puerta abierta
    double angle = (atan2(player.getY() - y, player.getX() - x) - M_PI) * 180 / M_PI;
    int angulosonido = (angle - player.getDirection());
    if (angulosonido > 180) {
      angulosonido -= 360;
    }
    if (angulosonido <-180) {
      angulosonido += 360;
    }
    if (angulosonido < 0) {
      angulosonido += 360;
    }
    snd_open.playInPosition(-1, 0, angulosonido, std::min(int(player.getDistanceToPoint(x, y) * 22), 255));
  }
  this->isClosed = isClosed;
}

void DoorTile::actualizar() {
  if (isClosed && (closed_percentage > 0.001)) {
    closed_percentage -= OPENING_SPEED;
    if (closed_percentage <= 0.001) {
      // Sonido de puerta cerrada
      double angle = (atan2(player.getY() - y, player.getX() - x) - M_PI) * 180 / M_PI;
    	int angulosonido = (angle - player.getDirection());
    	if (angulosonido > 180) {
    		angulosonido -= 360;
    	}
    	if (angulosonido <-180) {
    		angulosonido += 360;
    	}
  		if (angulosonido < 0) {
  			angulosonido += 360;
  		}
  		snd_close.playInPosition(-1, 0, angulosonido, std::min(int(player.getDistanceToPoint(x, y) * 22), 255));
    }
  } else if (!isClosed && (closed_percentage < 1)) {
    closed_percentage += OPENING_SPEED;
  }
}

double DoorTile::getClosedPercentage() const {
  return this->closed_percentage;
}
