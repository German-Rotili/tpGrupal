#include "World.h"

static bool compareDistances(ZRenderable* o1, ZRenderable* o2) {
    return (o1->getDistToPlayer() > o2->getDistToPlayer());
}


World::World(SdlRenderer& renderer, ClientSettings& settings, std::vector<std::vector<int>> & map) :
  renderer(renderer),
  worldMap(map),
  jugador(renderer, settings, 1.5, 2.5, -45, 100, 0, 3),
  hud_jugador(renderer, jugador, settings),
  rayCaster(settings),
  tx_objects(renderer, "textures/objects.png", 152, 0, 136),
  tx_walls(renderer, "textures/walls.png"),
  tx_guardDogDown(renderer, "textures/enemies/guardDog/down_strip5.png", 152, 0, 136),
  tx_guardDogDownLeft(renderer, "textures/enemies/guardDog/downleft_strip5.png", 152, 0, 136),
  tx_guardDogLeft(renderer, "textures/enemies/guardDog/left_strip5.png", 152, 0, 136),
  tx_guardDogUpLeft(renderer, "textures/enemies/guardDog/upleft_strip5.png", 152, 0, 136),
  tx_guardDogUp(renderer, "textures/enemies/guardDog/up_strip5.png", 152, 0, 136),
  tx_guardDogShooting(renderer, "textures/enemies/guardDog/shooting_strip3.png", 152, 0, 136),
  tx_guardDogDying(renderer, "textures/enemies/guardDog/dying_strip5.png", 152, 0, 136),
  tx_guardDown(renderer, "textures/enemies/guard/down_strip5.png", 152, 0, 136),
  tx_guardDownLeft(renderer, "textures/enemies/guard/downleft_strip5.png", 152, 0, 136),
  tx_guardLeft(renderer, "textures/enemies/guard/left_strip5.png", 152, 0, 136),
  tx_guardUpLeft(renderer, "textures/enemies/guard/upleft_strip5.png", 152, 0, 136),
  tx_guardUp(renderer, "textures/enemies/guard/up_strip5.png", 152, 0, 136),
  tx_guardShooting(renderer, "textures/enemies/guard/shooting_strip3.png", 152, 0, 136),
  tx_guardDying(renderer, "textures/enemies/guard/dying_strip5.png", 152, 0, 136),
  tx_ssDown(renderer, "textures/enemies/ss/down_strip5.png"),
  tx_ssDownLeft(renderer, "textures/enemies/ss/downleft_strip5.png"),
  tx_ssLeft(renderer, "textures/enemies/ss/left_strip5.png"),
  tx_ssUpLeft(renderer, "textures/enemies/ss/upleft_strip5.png"),
  tx_ssUp(renderer, "textures/enemies/ss/up_strip5.png"),
  tx_ssShooting(renderer, "textures/enemies/ss/shooting_strip3.png"),
  tx_ssDying(renderer, "textures/enemies/ss/dying_strip5.png"),
  tx_officerDown(renderer, "textures/enemies/officer/down_strip5.png", 152, 0, 136),
  tx_officerDownLeft(renderer, "textures/enemies/officer/downleft_strip5.png", 152, 0, 136),
  tx_officerLeft(renderer, "textures/enemies/officer/left_strip5.png", 152, 0, 136),
  tx_officerUpLeft(renderer, "textures/enemies/officer/upleft_strip5.png", 152, 0, 136),
  tx_officerUp(renderer, "textures/enemies/officer/up_strip5.png", 152, 0, 136),
  tx_officerShooting(renderer, "textures/enemies/officer/shooting_strip3.png", 152, 0, 136),
  tx_officerDying(renderer, "textures/enemies/officer/dying_strip5.png", 152, 0, 136),
  tx_mutantDown(renderer, "textures/enemies/mutant/down_strip5.png", 0, 0, 128),
  tx_mutantDownLeft(renderer, "textures/enemies/mutant/downleft_strip5.png", 0, 0, 128),
  tx_mutantLeft(renderer, "textures/enemies/mutant/left_strip5.png", 0, 0, 128),
  tx_mutantUpLeft(renderer, "textures/enemies/mutant/upleft_strip5.png", 0, 0, 128),
  tx_mutantUp(renderer, "textures/enemies/mutant/up_strip5.png", 0, 0, 128),
  tx_mutantShooting(renderer, "textures/enemies/mutant/shooting_strip3.png", 0, 0, 128),
  tx_mutantDying(renderer, "textures/enemies/mutant/dying_strip5.png", 0, 0, 128) {
  std::vector<const SdlTexture*> sDown = {&tx_guardDogDown, &tx_guardDown, &tx_ssDown, &tx_officerDown, &tx_mutantDown};
  std::vector<const SdlTexture*> sDownLeft = {&tx_guardDogDownLeft, &tx_guardDownLeft, &tx_ssDownLeft, &tx_officerDownLeft, &tx_mutantDownLeft};
  std::vector<const SdlTexture*> sLeft = {&tx_guardDogLeft, &tx_guardLeft, &tx_ssLeft, &tx_officerLeft, &tx_mutantLeft};
  std::vector<const SdlTexture*> sUpLeft = {&tx_guardDogUpLeft, &tx_guardUpLeft, &tx_ssUpLeft, &tx_officerUpLeft, &tx_mutantUpLeft};
  std::vector<const SdlTexture*> sUp = {&tx_guardDogUp, &tx_guardUp, &tx_ssUp, &tx_officerUp, &tx_mutantUp};
  std::vector<const SdlTexture*> sShooting = {&tx_guardDogShooting, &tx_guardShooting, &tx_ssShooting, &tx_officerShooting, &tx_mutantShooting};
  std::vector<const SdlTexture*> sDying = {&tx_guardDogDying, &tx_guardDying, &tx_ssDying, &tx_officerDying, &tx_mutantDying};

  // Carga de objetos del mapa
  int ymap = 0;
  std::vector<std::vector<int>>::iterator row;
  std::vector<int>::iterator col;
  for (row = map.begin(); row != map.end(); row++) {
    int xmap = 0;
    for (col = row->begin(); col != row->end(); col++) {
        switch (*col) {
         case 36:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, barril_clip, tx_objects));
         break;
         case 37:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, pozo_clip, tx_objects));
         break;
         case 38:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, columna_clip, tx_objects));
         break;
         case 39:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, estatua_clip, tx_objects));
         break;
         case 40:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, lamp1_clip, tx_objects));
         break;
         case 41:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, lamp2_clip, tx_objects));
         break;
         case 42:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, charco_clip, tx_objects));
         break;
         case 43:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, huesos_clip, tx_objects));
         break;
       }
      xmap++;
    }
    ymap++;
  }

  enemigos.push_back(new Enemy(2.5, 4.5, enemy_clip, 0, sDown, sDownLeft, sLeft,
    sUpLeft, sUp, sShooting, sDying, settings));
}

World::~World() {
  // Borrar los elementos de todos los vectores
  for (std::vector<Object*>::iterator it = objetosConstantes.begin();
   it!= objetosConstantes.end(); ++it) {
    delete *it;
  }
  for (std::vector<Object*>::iterator it = objetosModificables.begin();
   it!= objetosModificables.end(); ++it) {
    delete *it;
  }
  for (std::vector<Enemy*>::iterator it = enemigos.begin();
   it!= enemigos.end(); ++it) {
    delete *it;
  }
}

void World::actualizar(double playerX, double playerY, double playerAngle,
  double playerHealth, int playerLives, int playerArmaActual, bool playerIsShooting,
  int playerScore,
  double enemyAngle, double enemyX, double enemyY, int enemyArmaActual,
  bool enemyIsAlive, bool enemyIsWalking, bool enemyIsShooting,
  bool allDoorsClosed) {
  jugador.setPosicion(playerX, playerY);
  jugador.setDirection(playerAngle);
  jugador.setHealth(playerHealth);
  jugador.setLives(playerLives);
  jugador.setArmaActual(playerArmaActual);
  jugador.setIsShooting(playerIsShooting);
  jugador.setScore(playerScore);
  // Faltan implementar: Llaves y actualizacion de balas.

  // Actualizo direccion de enemigos;
  enemigos.back()->setRelativeDirection(enemyAngle, jugador.getDirection()); // Hacerlo para cada enemigo
  enemigos.back()->setPosicion(enemyX, enemyY);
  enemigos.back()->setWeapon(enemyArmaActual);
  enemigos.back()->setIsAlive(enemyIsAlive);
  enemigos.back()->setIsRunning(enemyIsWalking);
  enemigos.back()->setIsShooting(enemyIsShooting);

  worldMap.setDoorsClosed(allDoorsClosed);

  worldMap.actualizar();
  hud_jugador.actualizar();

}

void World::renderizar(ClientSettings& settings) {
  //rayCaster.cast2D(renderer, jugador.getX(), jugador.getY(), jugador.getDirection(), settings);
  rayCaster.cast3D(renderer, worldMap, jugador.getX(), jugador.getY(), jugador.getDirection(), tx_walls, zBuffer, settings);

  std::vector<ZRenderable*> visibles;
  // obtengo objetos visibles
  for (std::vector<Object*>::iterator it = objetosConstantes.begin();
   it!= objetosConstantes.end(); ++it) {
     // (*it)->actualizar();
     if ((*it)->esVisibleDesde(jugador.getX(), jugador.getY(), jugador.getDirection(), settings)) {
       (*it)->updateDistToPlayer(jugador.getX(), jugador.getY(), settings);
       visibles.push_back((*it));
    }
  }

  // obtengo enemigos visibles
  for (std::vector<Enemy*>::iterator it = enemigos.begin();
   it!= enemigos.end(); ++it) {
     (*it)->actualizar();
     if ((*it)->esVisibleDesde(jugador.getX(), jugador.getY(), jugador.getDirection(), settings)) {
       (*it)->updateDistToPlayer(jugador.getX(), jugador.getY(), settings);
       visibles.push_back((*it));
    }
  }
  // ordeno los visibles de acuerdo a sus distancias
  std::sort(visibles.begin(), visibles.end(), compareDistances);
  // dibujo ordenadamente todos los visibles
  for (std::vector<ZRenderable*>::iterator it = visibles.begin();
   it!= visibles.end(); ++it) {
    (*it)->renderizar(renderer, zBuffer, settings);
  }

  jugador.renderizar(settings);
  hud_jugador.renderizar(settings);
  renderer.renderPresent();
}
