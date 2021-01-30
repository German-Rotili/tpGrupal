#ifndef MAP_UI
#define MAP_UI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "constants.h"

class Map_ui {
private:
  std::vector<std::vector<int>> map;

public:
  void createMap(int x, int y);

  int checkMap(int x, int y);

  void toggleTile(int x, int y, int action);

  void drawMap(SdlRenderer& renderer, SdlTexture& walls, SdlTexture& objects, int scrollX, int scrollY);

  void setMap(std::vector<std::vector<int>> map);

  std::vector<std::vector<int>> getMap();
};
#endif /* MAP_UI */
