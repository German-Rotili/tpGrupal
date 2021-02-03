#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "map_ui.h"
#include "constants.h"

void Map_ui::createMap(int x, int y) {
  map = std::vector<std::vector<int>>(y, std::vector<int>(x, 57));
}

int Map_ui::checkMap(int x, int y) {
  if (x < 0 || x >= map.at(0).size() || y < 0 || y >= map.size()) return 0;
  return map[y][x];
}

void Map_ui::toggleTile(int x, int y, int action) {
  map[y][x] = action;
}

void Map_ui::drawMap(SdlRenderer& renderer, SdlTexture& walls, SdlTexture& objects, int scrollX, int scrollY) {
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderClear();
  int wallIdX;
  int wallIdY;
  SDL_Rect clip;
  for (int i = scrollX; i < map.at(0).size(); i++) {
    for (int j = scrollY; j < map.size(); j++) {
      if (checkMap(i, j) >= 0 && checkMap(i, j) <= 33) {
        wallIdX = checkMap(i, j) % 3;
        wallIdY = (checkMap(i, j)) / 3;
        clip.x = wallIdX * TILE_SIZE;
        clip.y = wallIdY * TILE_SIZE;
        clip.w = TILE_SIZE;
        clip.h = TILE_SIZE;
        renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
      } else if (checkMap(i, j) >= 36 && checkMap(i, j) <= 56) {
        wallIdX = (checkMap(i, j) - 36) % 3;
        wallIdY = (checkMap(i, j) - 36) / 3;
        clip.x = wallIdX * TILE_SIZE;
        clip.y = wallIdY * TILE_SIZE;
        clip.w = TILE_SIZE;
        clip.h = TILE_SIZE;
        renderer.renderCopy(objects, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
      } else if (checkMap(i, j) == 34) {
        clip.x = 64;
        clip.y = 704;
        clip.w = 64;
        clip.h = 64;

        renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
        renderer.setRenderDrawColor(205, 133, 63, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE+30, 64, 4);
      } else if (checkMap(i, j) == 35) {
        clip.x = 64;
        clip.y = 704;
        clip.w = 64;
        clip.h = 64;

        renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
        renderer.setRenderDrawColor(205, 133, 63, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 30, (j-scrollY)*TILE_SIZE, 4, 64);
      } else if (checkMap(i, j) == 57) {
        renderer.setRenderDrawColor(0, 0, 0, 255);
        renderer.renderDrawRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, TILE_SIZE, TILE_SIZE);
      } else if (checkMap(i, j) == 58) {
        renderer.setRenderDrawColor(0, 255, 0, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, ((j-scrollY)*TILE_SIZE) + 28, 8, 8);
      } else if (checkMap(i, j) == 59) {
        clip.x = 128;
        clip.y = 704;
        clip.w = 64;
        clip.h = 64;

        renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
        renderer.setRenderDrawColor(212, 175, 55, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, (j-scrollY)*TILE_SIZE+28, 8, 8);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE+30, 64, 4);
      } else if (checkMap(i, j) == 60) {
        clip.x = 128;
        clip.y = 704;
        clip.w = 64;
        clip.h = 64;

        renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
        renderer.setRenderDrawColor(212, 175, 55, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, (j-scrollY)*TILE_SIZE+28, 8, 8);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 30, (j-scrollY)*TILE_SIZE, 4, 64);
      } else if (checkMap(i, j) == 61) {
        clip.x = 128;
        clip.y = 704;
        clip.w = 64;
        clip.h = 64;

        renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
        renderer.setRenderDrawColor(0, 173, 238, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, (j-scrollY)*TILE_SIZE+28, 8, 8);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE+30, 64, 4);
      } else if (checkMap(i, j) == 62) {
        clip.x = 128;
        clip.y = 704;
        clip.w = 64;
        clip.h = 64;

        renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
        renderer.setRenderDrawColor(0, 173, 238, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, (j-scrollY)*TILE_SIZE+28, 8, 8);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 30, (j-scrollY)*TILE_SIZE, 4, 64);
      } else if (checkMap(i, j) == 63) {
        renderer.setRenderDrawColor(205, 133, 63, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, ((j-scrollY)*TILE_SIZE) + 30, TILE_SIZE, 4);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, ((j-scrollY)*TILE_SIZE) + 28, 8, 8);
      } else if (checkMap(i, j) == 64) {
        renderer.setRenderDrawColor(205, 133, 63, 255);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 30, ((j-scrollY)*TILE_SIZE), 4, TILE_SIZE);
        renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, ((j-scrollY)*TILE_SIZE) + 28, 8, 8);
      }
    }
  }
}

void Map_ui::setMap(std::vector<std::vector<int>> map) {
  this->map = map;
}

std::vector<std::vector<int>> Map_ui::getMap() {
  return this->map;
}
