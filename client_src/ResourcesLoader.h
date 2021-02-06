#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlSound.h"


class ResourcesLoader {
public:
  // Texturas
  SdlTexture tx_objects;
  SdlTexture tx_rocket;
  SdlTexture tx_explosion;
  SdlTexture tx_walls;
  SdlTexture tx_guardDogDown;
  SdlTexture tx_guardDogDownLeft;
  SdlTexture tx_guardDogLeft;
  SdlTexture tx_guardDogUpLeft;
  SdlTexture tx_guardDogUp;
  SdlTexture tx_guardDogShooting;
  SdlTexture tx_guardDogDying;
  SdlTexture tx_guardDown;
  SdlTexture tx_guardDownLeft;
  SdlTexture tx_guardLeft;
  SdlTexture tx_guardUpLeft;
  SdlTexture tx_guardUp;
  SdlTexture tx_guardShooting;
  SdlTexture tx_guardDying;
  SdlTexture tx_ssDown;
  SdlTexture tx_ssDownLeft;
  SdlTexture tx_ssLeft;
  SdlTexture tx_ssUpLeft;
  SdlTexture tx_ssUp;
  SdlTexture tx_ssShooting;
  SdlTexture tx_ssDying;
  SdlTexture tx_officerDown;
  SdlTexture tx_officerDownLeft;
  SdlTexture tx_officerLeft;
  SdlTexture tx_officerUpLeft;
  SdlTexture tx_officerUp;
  SdlTexture tx_officerShooting;
  SdlTexture tx_officerDying;
  SdlTexture tx_mutantDown;
  SdlTexture tx_mutantDownLeft;
  SdlTexture tx_mutantLeft;
  SdlTexture tx_mutantUpLeft;
  SdlTexture tx_mutantUp;
  SdlTexture tx_mutantShooting;
  SdlTexture tx_mutantDying;

  // Sonidos
  SdlSound snd_cuchillo;
  SdlSound snd_pistola1;
  SdlSound snd_pistola2;
  SdlSound snd_ametralladora1;
  SdlSound snd_ametralladora2;
  SdlSound snd_canionDeCadena;
  SdlSound snd_lanzacohetes;

  SdlSound snd_dying;
  SdlSound snd_explosion;
  SdlSound snd_door_open;
  SdlSound snd_door_closed;


  ResourcesLoader(SdlRenderer& renderer);
  ~ResourcesLoader();
};

#endif  // RESOURCES_H
