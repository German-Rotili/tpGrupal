#include "World.h"

static bool compareDistances(ZRenderable* o1, ZRenderable* o2) {
    return (o1->getDistToPlayer() > o2->getDistToPlayer());
}


World::World(SdlRenderer& renderer, ClientSettings& settings, std::vector<std::vector<int>> & map) :
  renderer(renderer),
  src(renderer),
  settings(settings),
  jugador(renderer, src, settings, 1.5, 2.5, -45, 100, 0, 3),
  worldMap(map, jugador, src),
  hud_jugador(renderer, jugador, settings),
  music("../resources/music/music2.mp3"),
  rayCaster(src.tx_walls, settings) {

    music.play();
    // Carga de objetos del mapa
    cargarObjetosConstantes(map);

    objetosConstantes.push_back(new Object(2.5, 1.5, basic_clip, src.tx_rocket, jugador, settings));

    enemigos.push_back(new Enemy(2.5, 4.5, basic_clip, 0, jugador, src, settings));
}

void World::cargarObjetosConstantes(std::vector<std::vector<int>> & map) {
  int ymap = 0;
  std::vector<std::vector<int>>::iterator row;
  std::vector<int>::iterator col;
  for (row = map.begin(); row != map.end(); row++) {
    int xmap = 0;
    for (col = row->begin(); col != row->end(); col++) {
        switch (*col) {
         case 36:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, barril_clip, src.tx_objects, jugador, settings));
         break;
         case 37:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, pozo_clip, src.tx_objects, jugador, settings));
         break;
         case 38:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, columna_clip, src.tx_objects, jugador, settings));
         break;
         case 39:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, estatua_clip, src.tx_objects, jugador, settings));
         break;
         case 40:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, lamp1_clip, src.tx_objects, jugador, settings));
         break;
         case 41:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, lamp2_clip, src.tx_objects, jugador, settings));
         break;
         case 42:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, charco_clip, src.tx_objects, jugador, settings));
         break;
         case 43:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, huesos_clip, src.tx_objects, jugador, settings));
         break;
       }
      xmap++;
    }
    ymap++;
  }
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
       delete *it;
       explosiones.erase(it);
       --it;
     }
  }
  // Agrego explosion si no hay:
  if ((!allDoorsClosed) & (explosiones.size() == 0)) {
    //explosiones.push_back(new Explosion(7.5, 2.5 , basic_clip, jugador, src, settings));
  }
  //

  worldMap.actualizar();
  hud_jugador.actualizar();
}

void World::renderizar(ClientSettings& settings) {
  //rayCaster.cast2D(renderer, jugador.getX(), jugador.getY(), jugador.getDirection(), settings);
  rayCaster.cast3D(renderer, worldMap, jugador.getX(), jugador.getY(), jugador.getDirection(), settings);

  std::vector<ZRenderable*> visibles;
  // obtengo objetos visibles
  for (std::vector<Object*>::iterator it = objetosConstantes.begin();
   it!= objetosConstantes.end(); ++it) {
     // (*it)->actualizar();
     if ((*it)->esVisiblePorPlayer(settings)) {
       (*it)->updateDistToPlayer();
       visibles.push_back((*it));
    }
  }

  // obtengo explosiones visibles
  for (std::vector<Explosion*>::iterator it = explosiones.begin();
   it!= explosiones.end(); ++it) {
     (*it)->actualizar();
     if ((*it)->esVisiblePorPlayer(settings)) {
       (*it)->updateDistToPlayer();
       visibles.push_back((*it));
    }
  }

  // obtengo enemigos visibles
  for (std::vector<Enemy*>::iterator it = enemigos.begin();
   it!= enemigos.end(); ++it) {
     (*it)->actualizar();
     if ((*it)->esVisiblePorPlayer(settings)) {
       (*it)->updateDistToPlayer();
       visibles.push_back((*it));
    }
  }
  // ordeno los visibles de acuerdo a sus distancias
  std::sort(visibles.begin(), visibles.end(), compareDistances);
  // dibujo ordenadamente todos los visibles
  for (std::vector<ZRenderable*>::iterator it = visibles.begin();
   it!= visibles.end(); ++it) {
    (*it)->renderizar(renderer, rayCaster.zBuffer, settings);
  }

  jugador.renderizar(settings);
  hud_jugador.renderizar(settings);
  renderer.renderPresent();
}
