#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <algorithm>
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "ZRenderable.h"
#include "Object.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Player.h"
#include "Hud.h"
#include "rayCaster.h"
#include "Map/WorldMap.h"

class World {
  SdlRenderer& renderer;
  WorldMap worldMap;
  std::vector<Object*> objetosConstantes;
  std::vector<Object*> objetosDinamicos;
  std::vector<Explosion*> explosiones;
  std::vector<Enemy*> enemigos;
  Player jugador;
  Hud hud_jugador;

  double zBuffer[1024];
  RayCaster rayCaster;

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



  SDL_Rect basic_clip = {0, 0, 64, 64};

  SDL_Rect barril_clip = {64*0, 64*0, 64, 64};
  SDL_Rect pozo_clip = {64*1, 64*0, 64, 64};
  SDL_Rect columna_clip = {64*2, 64*0, 64, 64};
  SDL_Rect estatua_clip = {64*0, 64*1, 64, 64};
  SDL_Rect lamp1_clip = {64*1, 64*1, 64, 64};
  SDL_Rect lamp2_clip = {64*2, 64*1, 64, 64};
  SDL_Rect charco_clip = {64*0, 64*2, 64, 64};
  SDL_Rect huesos_clip = {64*1, 64*2, 64, 64};
  SDL_Rect llave1_clip = {64*2, 64*2, 64, 64};
  SDL_Rect llave2_clip = {64*0, 64*3, 64, 64};
  SDL_Rect sangre_clip = {64*1, 64*3, 64, 64};
  SDL_Rect comida_clip = {64*2, 64*3, 64, 64};
  SDL_Rect kit_clip = {64*0, 64*4, 64, 64};
  SDL_Rect balas_clip = {64*1, 64*4, 64, 64};
  SDL_Rect ametralladora_clip = {64*2, 64*4, 64, 64};
  SDL_Rect canionDeCadena_clip = {64*0, 64*5, 64, 64};
  SDL_Rect lanzacohetes_clip = {64*1, 64*5, 64, 64};
  SDL_Rect cruz_clip = {64*2, 64*5, 64, 64};
  SDL_Rect copa_clip = {64*0, 64*6, 64, 64};
  SDL_Rect cofre_clip = {64*1, 64*6, 64, 64};
  SDL_Rect corona_clip = {64*2, 64*6, 64, 64};

	public:
//		World(SdlRenderer& renderer, ClientSettings& settings);
		World(SdlRenderer& renderer, ClientSettings& settings, std::vector<std::vector<int>> & map);
    ~World();
    void actualizar(double playerX, double playerY, double playerAngle,
      double playerHealth, int playerLives, int playerArmaActual,
      bool playerIsShooting, int playerScore,
      double enemyAngle, double enemyX, double enemyY, int enemyArmaActual,
      bool enemyIsAlive, bool enemyIsWalking, bool enemyIsShooting,
      bool allDoorsClosed);
    void renderizar(ClientSettings& settings);
};

#endif  // WORLD_H
