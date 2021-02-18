#include "World.h"

static bool compareDistances(ZRenderable* o1, ZRenderable* o2) {
    return (o1->getDistToPlayer() > o2->getDistToPlayer());
}


World::World(SdlRenderer& renderer, ClientSettings& settings, std::vector<std::vector<int>> & map) :
  renderer(renderer),
  src(renderer),
  settings(settings),
  myPlayer(renderer, src, settings, 1.5, 2.5, -45, 100, 0, 3),
  worldMap(map, myPlayer, src),
  hud_jugador(renderer, myPlayer, settings),
  music("../resources/music/music2.mp3"),
  rayCaster(src.tx_walls, settings) {
    music.play();
    // Carga de objetos del mapa
    cargarObjetosConstantes(map);
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
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, barril_clip, src.tx_objects, myPlayer, settings));
         break;
         case 37:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, pozo_clip, src.tx_objects, myPlayer, settings));
         break;
         case 38:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, columna_clip, src.tx_objects, myPlayer, settings));
         break;
         case 39:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, estatua_clip, src.tx_objects, myPlayer, settings));
         break;
         case 40:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, lamp1_clip, src.tx_objects, myPlayer, settings));
         break;
         case 41:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, lamp2_clip, src.tx_objects, myPlayer, settings));
         break;
         case 42:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, charco_clip, src.tx_objects, myPlayer, settings));
         break;
         case 43:
         objetosConstantes.push_back(new Object(xmap + 0.5, ymap + 0.5, huesos_clip, src.tx_objects, myPlayer, settings));
         break;
       }
      xmap++;
    }
    ymap++;
  }
}

World::~World() {
  std::cout << "Destruyendo world" << std::endl;
  // Borrar los elementos de todos los vectores y el map de enemigos
  for (std::vector<Object*>::iterator it = objetosConstantes.begin();
   it!= objetosConstantes.end(); ++it) {
    delete *it;
  }
  limpiarObjetosDinamicos();

  for (std::vector<Explosion*>::iterator it = explosiones.begin();
   it!= explosiones.end(); ++it) {
    delete *it;
  }
  for (std::map<int, Enemy*>::iterator it = enemigos.begin();
   it!= enemigos.end(); ++it) {
    delete (*it).second;
  }

}

void World::limpiarObjetosDinamicos() {
  for (std::vector<Object*>::iterator it = objetosDinamicos.begin();
   it!= objetosDinamicos.end(); ++it) {
    delete *it;
  }
}

void World::agregarObjetoDinamico(object_t & object) {
  double x = object.pos_x + 0.5;
  double y = object.pos_y + 0.5;
  switch (object.id) {
    case 35:
    objetosDinamicos.push_back(new Object(x, y, basic_clip, src.tx_rocket, myPlayer, settings));
    break;
    case 44:
    objetosDinamicos.push_back(new Object(x, y, llave1_clip, src.tx_objects, myPlayer, settings));
    break;
    case 45:
    objetosDinamicos.push_back(new Object(x, y, llave2_clip, src.tx_objects, myPlayer, settings));
    break;
    case 46:
    objetosDinamicos.push_back(new Object(x, y, sangre_clip, src.tx_objects, myPlayer, settings));
    break;
    case 47:
    objetosDinamicos.push_back(new Object(x, y, comida_clip, src.tx_objects, myPlayer, settings));
    break;
    case 48:
    objetosDinamicos.push_back(new Object(x, y, kit_clip, src.tx_objects, myPlayer, settings));
    break;
    case 49:
    objetosDinamicos.push_back(new Object(x, y, balas_clip, src.tx_objects, myPlayer, settings));
    break;
    case 50:
    objetosDinamicos.push_back(new Object(x, y, ametralladora_clip, src.tx_objects, myPlayer, settings));
    break;
    case 51:
    objetosDinamicos.push_back(new Object(x, y, canionDeCadena_clip, src.tx_objects, myPlayer, settings));
    break;
    case 52:
    objetosDinamicos.push_back(new Object(x, y, lanzacohetes_clip, src.tx_objects, myPlayer, settings));
    break;
    case 53:
    objetosDinamicos.push_back(new Object(x, y, cruz_clip, src.tx_objects, myPlayer, settings));
    break;
    case 54:
    objetosDinamicos.push_back(new Object(x, y, copa_clip, src.tx_objects, myPlayer, settings));
    break;
    case 55:
    objetosDinamicos.push_back(new Object(x, y, cofre_clip, src.tx_objects, myPlayer, settings));
    break;
    case 56:
    objetosDinamicos.push_back(new Object(x, y, corona_clip, src.tx_objects, myPlayer, settings));
    break;
  }
}

void World::update(Snapshot & snapshot, ProtectedQueueAction & actions) {
    for (auto &player : snapshot.players) {
      if (player.player_id == settings.myCurrentId){
        myPlayer.setPosicion(player.pos_x , player.pos_y);
        myPlayer.setDirection(player.direction);
        myPlayer.setHealth(player.health);
        myPlayer.setLives(player.lives);
        myPlayer.setArmaActual(player.current_weapon);
        myPlayer.setScore(player.score);
      } else {
        if (enemigos.find(player.player_id) == enemigos.end()) {
          enemigos.insert(std::pair<int, Enemy*>(player.player_id, new Enemy(-1, -1, basic_clip, 0, myPlayer, src, settings)));
        }
        enemigos.at(player.player_id)->setRelativeDirection(player.direction, myPlayer.getDirection());  // Esto puede dar pequeños bugs visuales si se actualiza primero el enemigo y luego el myPlayer
        bool seMovio = enemigos.at(player.player_id)->setPosicion(player.pos_x, player.pos_y);
        enemigos.at(player.player_id)->setIsRunning(seMovio);
        enemigos.at(player.player_id)->setWeapon(player.current_weapon);
        enemigos.at(player.player_id)->setIsAlive(player.health > 0);
      }
    }
    int actions_processed = 0;
    while(!actions.is_empty() || actions_processed == MAX_ACTIONS_PROCESSED){
      actions_processed +=1;
      Action action = actions.get_element();
      if (action.get_id() == -1){ // Caso explosion
        explosiones.push_back(new Explosion(action.impact_x, action.impact_y, basic_clip, myPlayer, src.tx_explosion,src.snd_explosion, settings));
      } else if (action.get_id() == settings.myCurrentId) {  // caso disparo myPlayer
        myPlayer.setShootingAction();
        explosiones.push_back(new Explosion(action.impact_x, action.impact_y, basic_clip, myPlayer, src.tx_bullethit,src.snd_bullethit, settings));
      } else if (enemigos.find(action.get_id()) != enemigos.end()) {  // caso disparo enemigo
        enemigos.at(action.get_id())->setShootingAction();
        explosiones.push_back(new Explosion(action.impact_x, action.impact_y, basic_clip, myPlayer, src.tx_bullethit,src.snd_bullethit, settings));
      } else {
        continue;
      }
    }

  // update objetos / puertas
  limpiarObjetosDinamicos();
  objetosDinamicos.resize(0);
  for (auto &object : snapshot.objects){
    if ((object.id) == 34) {
      worldMap.setEstadoPuerta(object.pos_x, object.pos_y, object.state);
    } else {
      agregarObjetoDinamico(object);
    }
  }
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

  worldMap.update();
  hud_jugador.update();
}

void World::render(ClientSettings& settings) {
  rayCaster.cast3D(renderer, worldMap, myPlayer, settings);

  std::vector<ZRenderable*> visibles;
  // obtengo objetos visibles
  for (std::vector<Object*>::iterator it = objetosConstantes.begin();
   it!= objetosConstantes.end(); ++it) {
     if ((*it)->esVisiblePorPlayer(settings)) {
       (*it)->updateDistToPlayer();
       visibles.push_back((*it));
    }
  }
  for (std::vector<Object*>::iterator it = objetosDinamicos.begin();
   it!= objetosDinamicos.end(); ++it) {
     if ((*it)->esVisiblePorPlayer(settings)) {
       (*it)->updateDistToPlayer();
       visibles.push_back((*it));
    }
  }

  // obtengo explosiones visibles
  for (std::vector<Explosion*>::iterator it = explosiones.begin();
   it!= explosiones.end(); ++it) {
     (*it)->update();
     if ((*it)->esVisiblePorPlayer(settings)) {
       (*it)->updateDistToPlayer();
       visibles.push_back((*it));
    }
  }

  // obtengo enemigos visibles
  for (std::map<int, Enemy*>::iterator it = enemigos.begin();
   it!= enemigos.end(); ++it) {
     (*it).second->update();
     if ((*it).second->esVisiblePorPlayer(settings)) {
       (*it).second->updateDistToPlayer();
       visibles.push_back((*it).second);
    }
  }
  // ordeno los visibles de acuerdo a sus distancias
  std::sort(visibles.begin(), visibles.end(), compareDistances);
  // dibujo ordenadamente todos los visibles
  for (std::vector<ZRenderable*>::iterator it = visibles.begin();
   it!= visibles.end(); ++it) {
    (*it)->render(renderer, rayCaster.zBuffer, settings);
  }

  myPlayer.render(settings);
  hud_jugador.render(settings);
  renderer.renderPresent();
}
