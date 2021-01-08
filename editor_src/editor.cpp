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

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 640
#define MAP_Y 12
#define MAP_X 12

std::vector<std::vector<int>> createMap(int x, int y) {
  return std::vector<std::vector<int>>(y, std::vector<int>(x, 0));
}

int checkMap(int x, int y, std::vector<std::vector<int>>& map) {
  if (x < 0 || x >= map.at(0).size() || y < 0 || y >= map.size()) return 0;
  return map[y][x];
}

void toggleTile(int x, int y, int action, std::vector<std::vector<int>>& map) {
  if (map[y][x] == 3) {
    if (action == 3) {
      map[y][x] = 4;
      return;
    }
  }
  map[y][x] = action;
}

int main(int argc, char* args[]) {
  try {
    SdlContexto contexto;  // Inicializa SDL y SDL_image

    SdlWindow window("Wolfenstein_Editor", SCREEN_WIDTH, SCREEN_HEIGHT);

    SdlRenderer renderer = window.getRenderer();

    SdlTexture walls(renderer, "textures/walls.png");

    int playerx = SCREEN_WIDTH/2;
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
            if (scrollX < map.at(1).size() - ((SCREEN_WIDTH - 128)/64))
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
            if (e.button.x > 128) {
              int x = int((e.button.x - 128) / 64);
              int y = int(e.button.y / 64);
              toggleTile(x+scrollX, y+scrollY, action, map);
            } else if ((e.button.x >= 32 && e.button.x <= 96) &&
              (e.button.y >= SCREEN_HEIGHT/5 &&
              e.button.y <= (SCREEN_HEIGHT/5) + 64)) {
              action = 0;
            } else if ((e.button.x >= 32 && e.button.x <= 96) &&
              (e.button.y >= 2 * (SCREEN_HEIGHT/5) &&
              e.button.y <= (2 * (SCREEN_HEIGHT/5)) + 64)) {
              action = 1;
            } else if ((e.button.x >= 32 && e.button.x <= 96) &&
              (e.button.y >= 3 * (SCREEN_HEIGHT/5) &&
              e.button.y <= (3 * (SCREEN_HEIGHT/5)) + 64)) {
              action = 2;
            } else if ((e.button.x >= 32 && e.button.x <= 96) &&
              (e.button.y >= 4 * (SCREEN_HEIGHT/5) &&
              e.button.y <= (4 * (SCREEN_HEIGHT/5)) + 64)) {
              action = 3;
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
          if (checkMap(i, j, map) == 1) {
            clip.x = wallIdX * 64;
            clip.y = wallIdY * 64;
            clip.w = 64;
            clip.h = 64;
            renderer.renderCopy(walls, &clip, ((i-scrollX)*64) + 128, (j-scrollY)*64, 1, 1);
          }
          renderer.setRenderDrawColor(0, 0, 0, 255);
          renderer.renderDrawRect(((i-scrollX)*64) + 128, (j-scrollY)*64, 64, 64);
          if (checkMap(i, j, map) == 2) {
            renderer.setRenderDrawColor(0, 255, 0, 255);
            renderer.renderFillRect(((i-scrollX)*64) + 156, ((j-scrollY)*64) + 28, 8, 8);
          } else if (checkMap(i, j, map) == 3) {
            renderer.setRenderDrawColor(205, 133, 63, 255);
            renderer.renderFillRect(((i-scrollX)*64) + 128, ((j-scrollY)*64) + 30, 64, 4);
          } else if (checkMap(i, j, map) == 4) {
            renderer.setRenderDrawColor(205, 133, 63, 255);
            renderer.renderFillRect(((i-scrollX)*64) + 158, ((j-scrollY)*64), 4, 64);
          }
        }
      }

      clip.x = wallIdX * 64;
      clip.y = wallIdX * 64;
      clip.w = 64;
      clip.h = 64;

      renderer.setRenderDrawColor(100, 100, 100, 255);
      renderer.renderFillRect(0, 0, 128, SCREEN_HEIGHT);

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderFillRect(32, SCREEN_HEIGHT/5, 64, 64);

      renderer.renderCopy(walls, &clip, 32, 2 * (SCREEN_HEIGHT/5), 1, 1);

      renderer.setRenderDrawColor(0, 255, 0, 255);
      renderer.renderFillRect(60, (3 * (SCREEN_HEIGHT/5)) + 30, 8, 8);

      renderer.setRenderDrawColor(205, 133, 63, 255);
      renderer.renderFillRect(32, (4 * (SCREEN_HEIGHT/5)) + 30, 64, 4);

      renderer.setRenderDrawColor(255, 165, 0, 255);
      renderer.renderDrawRect(32, (action+1) * (SCREEN_HEIGHT/5), 64, 64);

      renderer.renderCopyCentered(tx_save_button, NULL, 30, 20);
      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderDrawRect(5, 5, 50, 35);

      renderer.renderCopyCentered(tx_load_button, NULL, 90, 20);
      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderDrawRect(65, 5, 50, 35);

      if (renderText) {
        SdlTexture tx_inputText(renderer, text_font, inputText, 255, 255, 255);
        renderer.setRenderDrawColor(100, 100, 100, 255);
        renderer.renderFillRect((SCREEN_WIDTH/2)-128, (SCREEN_HEIGHT/2)-16, 256, 32);
        renderer.renderCopyCentered(tx_inputText, NULL, (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2));
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
