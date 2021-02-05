#include "World.h"

static bool compareDistances(ZRenderable* o1, ZRenderable* o2) {
    return (o1->getDistToPlayer() > o2->getDistToPlayer());
}


World::World(SdlRenderer& renderer, ClientSettings& settings, std::vector<std::vector<int>> & map) :
  renderer(renderer),
  rc(renderer),
  settings(settings),
  worldMap(map),
  jugador(renderer, rc, settings, 1.5, 2.5, -45, 100, 0, 3),
  hud_jugador(renderer, jugador, settings),
  rayCaster(settings)
  {
  std::vector<const SdlTexture*> sDown = {&rc.tx_guardDogDown, &rc.tx_guardDown, &rc.tx_ssDown, &rc.tx_officerDown, &rc.tx_mutantDown};
  std::vector<const SdlTexture*> sDownLeft = {&rc.tx_guardDogDownLeft, &rc.tx_guardDownLeft, &rc.tx_ssDownLeft, &rc.tx_officerDownLeft, &rc.tx_mutantDownLeft};
  std::vector<const SdlTexture*> sLeft = {&rc.tx_guardDogLeft, &rc.tx_guardLeft, &rc.tx_ssLeft, &rc.tx_officerLeft, &rc.tx_mutantLeft};
  std::vector<const SdlTexture*> sUpLeft = {&rc.tx_guardDogUpLeft, &rc.tx_guardUpLeft, &rc.tx_ssUpLeft, &rc.tx_officerUpLeft, &rc.tx_mutantUpLeft};
  std::vector<const SdlTexture*> sUp = {&rc.tx_guardDogUp, &rc.tx_guardUp, &rc.tx_ssUp, &rc.tx_officerUp, &rc.tx_mutantUp};
  std::vector<const SdlTexture*> sShooting = {&rc.tx_guardDogShooting, &rc.tx_guardShooting, &rc.tx_ssShooting, &rc.tx_officerShooting, &rc.tx_mutantShooting};
  std::vector<const SdlTexture*> sDying = {&rc.tx_guardDogDying, &rc.tx_guardDying, &rc.tx_ssDying, &rc.tx_officerDying, &rc.tx_mutantDying};

  // Carga de objetos del mapa
  int ymap = 0;
  std::vector<std::vector<int>>::iterator row;
  std::vector<int>::iterator col;
  for (row = map.begin(); row != map.end(); row++) {
    int xmap = 0;
    for (col = row->begin(); col != row->end(); col++) {
        switch (*col) {
         case 36:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, barril_clip, rc.tx_objects, settings));
         break;
         case 37:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, pozo_clip, rc.tx_objects, settings));
         break;
         case 38:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, columna_clip, rc.tx_objects, settings));
         break;
         case 39:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, estatua_clip, rc.tx_objects, settings));
         break;
         case 40:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, lamp1_clip, rc.tx_objects, settings));
         break;
         case 41:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, lamp2_clip, rc.tx_objects, settings));
         break;
         case 42:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, charco_clip, rc.tx_objects, settings));
         break;
         case 43:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, huesos_clip, rc.tx_objects, settings));
         break;
       }
      xmap++;
    }
    ymap++;
  }

  objetosConstantes.push_back(new Object(2.5, 1.5, basic_clip, rc.tx_rocket, settings));

  enemigos.push_back(new Enemy(2.5, 4.5, basic_clip, 0, sDown, sDownLeft, sLeft,
    sUpLeft, sUp, sShooting, sDying, settings));
}

World::~World() {
  // Borrar los elementos de todos los vectores
  for (std::vector<Object*>::iterator it = objetosConstantes.begin();
   it!= objetosConstantes.end(); ++it) {
    delete *it;
  }
  for (std::vector<Object*>::iterator it = objetosDinamicos.begin();
   it!= objetosDinamicos.end(); ++it) {
    delete *it;
  }
  for (std::vector<Explosion*>::iterator it = explosiones.begin();
   it!= explosiones.end(); ++it) {
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

  // Provisorio para explosiones:
  // elimino explosiones terminadas.
  for (std::vector<Explosion*>::iterator it = explosiones.begin();
   it!= explosiones.end(); ++it) {
     if ((*it)->isFinished()) {
       delete *it; // Esto podria traer error si el vector se queda con esa instancia liberada.
       explosiones.erase(it);
       --it;
     }
  }
  // Agrego explosion si no hay:
  if ((!allDoorsClosed) & (explosiones.size() == 0)) {
    explosiones.push_back(new Explosion(3.5, 1.5 , basic_clip, rc.tx_explosion, settings));
    explosiones.push_back(new Explosion(5.5, 1.5 , basic_clip, rc.tx_explosion, settings));
    explosiones.push_back(new Explosion(7.5, 2.5 , basic_clip, rc.tx_explosion, settings));
  }
  //

  worldMap.actualizar();
  hud_jugador.actualizar();
}

void World::renderizar(ClientSettings& settings) {
  //rayCaster.cast2D(renderer, jugador.getX(), jugador.getY(), jugador.getDirection(), settings);
  rayCaster.cast3D(renderer, worldMap, jugador.getX(), jugador.getY(), jugador.getDirection(), rc.tx_walls, zBuffer, settings);

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

  // obtengo explosiones visibles
  for (std::vector<Explosion*>::iterator it = explosiones.begin();
   it!= explosiones.end(); ++it) {
     (*it)->actualizar();
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
