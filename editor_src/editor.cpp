#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "SDLWrappers/SdlFont.h"
#include "ConfigManager/MapHandler.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define MAP_Y 12
#define MAP_X 12
/* (64 * 6 == 384) */
#define MENU_OFFSET 384
#define TILE_SIZE 64


std::vector<std::vector<int>> createMap(int x, int y) {
  return std::vector<std::vector<int>>(y, std::vector<int>(x, 42));
}

int checkMap(int x, int y, std::vector<std::vector<int>>& map) {
  if (x < 0 || x >= map.at(0).size() || y < 0 || y >= map.size()) return 0;
  return map[y][x];
}

void toggleTile(int x, int y, int action, std::vector<std::vector<int>>& map) {
  if (map[y][x] == 44) {
    if (action == 44) {
      map[y][x] = 45;
      return;
    }
  }
  map[y][x] = action;
}

int main(int argc, char* args[]) {
  try {
    SdlContexto contexto;  // Inicializa SDL y SDL_image

    int realWidth = SCREEN_WIDTH + MENU_OFFSET;

    SdlWindow window("Wolfenstein_Editor", realWidth, SCREEN_HEIGHT);

    SdlRenderer renderer = window.getRenderer();

    SdlTexture walls(renderer, "textures/walls.png");

    int playerx = realWidth/2;
    int playery = SCREEN_HEIGHT/2;

    SdlFont font("fonts/wolfenstein.ttf", 30);
    SdlTexture tx_load_button(renderer, font, "Load", 255, 255, 255);
    SdlTexture tx_save_button(renderer, font, "Save", 255, 255, 255);

    SdlFont text_font("fonts/wolfenstein.ttf", 24);

    double actorX = 1;
    double actorY = 4;

    int action = 0;
    int scrollY = 0;
    int scrollX = 0;
    int wallIdX = 0;
    int wallIdY = 0;

    std::string inputText = " ";
    bool renderText = false;
    bool save = false, load = false;

    std::vector<std::vector<int>> map = createMap(MAP_Y, MAP_X);
    MapHandler mapHandler;

    //SdlTexture walls("textures/walls.png", renderer);

    bool quit = false;
    SDL_Event e;
    // Main (o game) Loop
    while (!quit) {
      // Event Loop
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN && save == false && load == false) {
          switch (e.key.keysym.sym) {
            case SDLK_UP:
            if (scrollY > 0)
              scrollY -= 1;
            break;

            case SDLK_DOWN:
            if (scrollY < map.size() - (SCREEN_HEIGHT/64))
              scrollY += 1;
            break;

            case SDLK_LEFT:
            if (scrollX > 0)
              scrollX -= 1;
            break;

            case SDLK_RIGHT:
            if (scrollX < map.at(1).size() - ((realWidth - MENU_OFFSET)/64))
              scrollX += 1;
            break;
          }
        } else if (e.type == SDL_KEYDOWN && (save == true || load == true)) {
          switch (e.key.keysym.sym) {
            case SDLK_RETURN:
            if (save == true) {
              mapHandler.emitMap(inputText, map);
            } else if  (load == true) {
              map = mapHandler.readMap(inputText);
            }
            renderText = false;
            break;

            case SDLK_BACKSPACE:
            if (inputText.length() > 0) {
              inputText.pop_back();
              renderText = true;
            }
            break;

            case SDLK_c:
            if (SDL_GetModState() & KMOD_CTRL) {
              SDL_SetClipboardText(inputText.c_str());
            }
            break;

            case SDLK_v:
            if (SDL_GetModState() & KMOD_CTRL) {
              inputText = SDL_GetClipboardText();
              renderText = true;
            }
            break;
          }
        } else if (e.type == SDL_TEXTINPUT) {
          if(!( SDL_GetModState() & KMOD_CTRL && (e.text.text[ 0 ] == 'c' ||
          e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' ||
          e.text.text[ 0 ] == 'V' ))) {
            inputText += e.text.text;
            renderText = true;
          }
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
          if (e.button.button == SDL_BUTTON_LEFT) {
            if (e.button.x > MENU_OFFSET) {
              int x = int((e.button.x - MENU_OFFSET) / TILE_SIZE);
              int y = int(e.button.y / TILE_SIZE);
              toggleTile(x+scrollX, y+scrollY, action, map);
            } else if (e.button.y >= 64 && e.button.y <= 576) {
              wallIdX = int(e.button.x / 64);
              wallIdY = int((e.button.y - 64) / 64);
              action = wallIdX + (wallIdY*6);
            } else if ((e.button.x >= 5 && e.button.x <= 55) &&
              (e.button.y >= 5 && e.button.y <= 40)) {
              save = true;
              load = false;
              renderText = true;
            } else if ((e.button.x >= 65 && e.button.x <= 115) &&
              (e.button.y >= 5 && e.button.y <= 40)) {
              load = true;
              save = false;
              renderText = true;
            }
            // } else if ((e.button.x >= 32 && e.button.x <= 96) &&
            //   (e.button.y >= SCREEN_HEIGHT/5 &&
            //   e.button.y <= (SCREEN_HEIGHT/5) + TILE_SIZE)) {
            //   action = 0;
            // } else if ((e.button.x >= 32 && e.button.x <= 96) &&
            //   (e.button.y >= 2 * (SCREEN_HEIGHT/5) &&
            //   e.button.y <= (2 * (SCREEN_HEIGHT/5)) + TILE_SIZE)) {
            //   action = 1;
            // } else if ((e.button.x >= 32 && e.button.x <= 96) &&
            //   (e.button.y >= 3 * (SCREEN_HEIGHT/5) &&
            //   e.button.y <= (3 * (SCREEN_HEIGHT/5)) + TILE_SIZE)) {
            //   action = 2;
            // } else if ((e.button.x >= 32 && e.button.x <= 96) &&
            //   (e.button.y >= 4 * (SCREEN_HEIGHT/5) &&
            //   e.button.y <= (4 * (SCREEN_HEIGHT/5)) + TILE_SIZE)) {
            //   action = 3;
            // } else if ((e.button.x >= 5 && e.button.x <= 55) &&
            //   (e.button.y >= 5 && e.button.y <= 40)) {
            //   save = true;
            //   load = false;
            //   renderText = true;
            // } else if ((e.button.x >= 65 && e.button.x <= 115) &&
            //   (e.button.y >= 5 && e.button.y <= 40)) {
            //   load = true;
            //   save = false;
            //   renderText = true;
            // }
          }
        }
      }

      // std::cout << map.at(0).size() << "\n";
      // std::cout << map.size() << "\n";

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderClear();
      int start = 0;
      SDL_Rect clip;
      // Dibujar mapa
      for (int i = scrollX; i < map.at(0).size(); i++) {
        for (int j = scrollY; j < map.size(); j++) {
          if (checkMap(i, j, map) >= 0 && checkMap(i, j, map) <= 41) {
            wallIdX = checkMap(i, j, map) % 6;
            wallIdY = (checkMap(i, j, map) - wallIdX) / 6;
            clip.x = wallIdX * TILE_SIZE;
            clip.y = wallIdY * TILE_SIZE;
            clip.w = TILE_SIZE;
            clip.h = TILE_SIZE;
            renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
          } else if (checkMap(i, j, map) == 42) {
            renderer.setRenderDrawColor(0, 0, 0, 255);
            renderer.renderDrawRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, TILE_SIZE, TILE_SIZE);
          } else if (checkMap(i, j, map) == 43) {
            renderer.setRenderDrawColor(0, 255, 0, 255);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, ((j-scrollY)*TILE_SIZE) + 28, 8, 8);
          } else if (checkMap(i, j, map) == 44) {
            renderer.setRenderDrawColor(205, 133, 63, 255);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, ((j-scrollY)*TILE_SIZE) + 30, TILE_SIZE, 4);
          } else if (checkMap(i, j, map) == 45) {
            renderer.setRenderDrawColor(205, 133, 63, 255);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 32, ((j-scrollY)*TILE_SIZE), 4, TILE_SIZE);
          }
        }
      }

      SDL_Rect clipMenu;
      clipMenu.x = 0;
      clipMenu.y = 0;
      clipMenu.w = 384;
      clipMenu.h = 448;

      wallIdX = action % 6;
      wallIdY = (action - wallIdX) / 6;

      renderer.setRenderDrawColor(100, 100, 100, 255);
      renderer.renderFillRect(0, 0, MENU_OFFSET, SCREEN_HEIGHT);

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderFillRect(0, 512, 64, 64);

      renderer.renderCopy(walls, &clipMenu, 0, 64, 1, 1);

      renderer.setRenderDrawColor(0, 255, 0, 255);
      renderer.renderFillRect(64+28, 512+28, 8, 8);

      renderer.setRenderDrawColor(205, 133, 63, 255);
      renderer.renderFillRect(128, 512+32, 64, 4);

      renderer.setRenderDrawColor(255, 165, 0, 255);
      renderer.renderDrawRect(wallIdX * 64, (wallIdY * 64) + 64, 64, 64);

      renderer.renderCopyCentered(tx_save_button, NULL, 30, 20);
      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderDrawRect(5, 5, 50, 35);

      renderer.renderCopyCentered(tx_load_button, NULL, 90, 20);
      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderDrawRect(65, 5, 50, 35);

      if (renderText) {
        SdlTexture tx_inputText(renderer, text_font, inputText, 255, 255, 255);
        renderer.setRenderDrawColor(100, 100, 100, 255);
        renderer.renderFillRect((realWidth/2)-128, (SCREEN_HEIGHT/2)-16, 256, 32);
        renderer.renderCopyCentered(tx_inputText, NULL, (realWidth/2), (SCREEN_HEIGHT/2));
      }

      renderer.renderPresent();

      SDL_Delay(1000/20);  // 20 fps por segundo
    }
  }
  catch (SdlException& e) {
    std::cout << e.what();
  }
  catch (...) {

  }
  return 0;
}
