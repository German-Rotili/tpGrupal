#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <algorithm>
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "ZRenderable.h"
#include "Object.h"
#include "Enemy.h"
#include "Player.h"
#include "Hud.h"
#include "rayCaster.h"
class World {
  // Map map;
  SdlRenderer& renderer;
  std::vector<Object*> objetosConstantes;
  std::vector<Object*> objetosModificables;
  std::vector<Enemy*> enemigos;
  Player jugador;
  Hud hud_jugador;

  double zBuffer[1024];
  RayCaster rayCaster;  // Auxiliar hasta que haga un refactor?

  SdlTexture tx_objects;
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



  SDL_Rect enemy_clip = {0, 0, 64, 64};
  SDL_Rect lamp_clip = {(64+1)*1, (64+1)*3, 64, 64};
  SDL_Rect barrel_clip = {(64+1)*3, (64+1)*0, 64, 64};
  SDL_Rect statue_clip = {(64+1)*3, (64+1)*3, 64, 64};

	public:
		World(SdlRenderer& renderer, ClientSettings& settings);
    ~World();
    void actualizar(double playerX, double playerY, double playerAngle,
      double playerHealth, int playerLives, int playerArmaActual,
      bool playerIsShooting, int playerScore,
      double enemyAngle, double enemyX, double enemyY, int enemyArmaActual,
      bool enemyIsAlive, bool enemyIsWalking, bool enemyIsShooting);
    void renderizar(ClientSettings& settings);
};

#endif  // WORLD_H
