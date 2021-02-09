#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlMusic.h"
#include "ClientSettings.h"
#include "ZRenderable.h"
#include "Object.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Player.h"
#include "Hud.h"
#include "rayCaster.h"
#include "Map/WorldMap.h"
#include "../common_src/Snapshot.h"
#include "../common_src/Action.h"
class World {
  SdlRenderer& renderer;
  ResourcesLoader src;
  ClientSettings& settings;
  Player jugador;
  WorldMap worldMap;
  int player_id;
  std::vector<Object*> objetosConstantes;
  std::vector<Object*> objetosDinamicos;
  std::vector<Explosion*> explosiones;
  std::map<int, Enemy*> enemigos;
  Hud hud_jugador;

  void cargarObjetosConstantes(std::vector<std::vector<int>> & map);
  void limpiarObjetosDinamicos();
  void agregarObjetoDinamico(object_t* object);

  SdlMusic music;
  RayCaster rayCaster;

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
		World(SdlRenderer& renderer, ClientSettings& settings, std::vector<std::vector<int>> & map, int player_id);
    ~World();
    void actualizar(Snapshot & snapshot);
    void renderizar(ClientSettings& settings);
};

#endif  // WORLD_H
