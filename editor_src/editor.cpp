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
/* (64 * 3 == 192) */
#define MENU_OFFSET 192
#define TILE_SIZE 64


std::vector<std::vector<int>> createMap(int x, int y) {
  return std::vector<std::vector<int>>(y, std::vector<int>(x, 57));
}

int checkMap(int x, int y, std::vector<std::vector<int>>& map) {
  if (x < 0 || x >= map.at(0).size() || y < 0 || y >= map.size()) return 0;
  return map[y][x];
}

void toggleTile(int x, int y, int action, std::vector<std::vector<int>>& map) {
  map[y][x] = action;
}

int main(int argc, char* args[]) {
  try {
    SdlContexto contexto;  // Inicializa SDL y SDL_image

    int realWidth = SCREEN_WIDTH + MENU_OFFSET;

    SdlWindow window("Wolfenstein_Editor", realWidth, SCREEN_HEIGHT);

    SdlRenderer renderer = window.getRenderer();

    SdlTexture walls(renderer, "textures/walls2.png");
    SdlTexture objects(renderer, "textures/objects2.png", 152, 0 , 136);

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
    int menuScrollX = 0;
    int IDScrollOffset = 0;
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

            case SDLK_d:
            if (menuScrollX < 2)
              menuScrollX += 1;
            break;

            case SDLK_a:
            if (menuScrollX > 0)
              menuScrollX -= 1;
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
        } else if (e.type == SDL_TEXTINPUT && (save == true || load == true)) {
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
            } else if (e.button.y >= 64 && e.button.y <= 640) {
              wallIdX = int(e.button.x / 64);
              wallIdY = int((e.button.y - 64) / 64);
              IDScrollOffset = menuScrollX;
              action = wallIdX + (wallIdY*3);
              if (IDScrollOffset == 1) {
                action += 27;
              } else if (IDScrollOffset == 2) {
                action += 27 * 2;
              }
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

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderClear();
      int start = 0;
      SDL_Rect clip;

      // Dibujar mapa
      for (int i = scrollX; i < map.at(0).size(); i++) {
        for (int j = scrollY; j < map.size(); j++) {
          if (checkMap(i, j, map) >= 0 && checkMap(i, j, map) <= 35) {
            wallIdX = checkMap(i, j, map) % 3;
            wallIdY = (checkMap(i, j, map)) / 3;
            clip.x = wallIdX * TILE_SIZE;
            clip.y = wallIdY * TILE_SIZE;
            clip.w = TILE_SIZE;
            clip.h = TILE_SIZE;
            renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
          } else if (checkMap(i, j, map) >= 36 && checkMap(i, j, map) <= 56) {
            wallIdX = (checkMap(i, j, map) - 36) % 3;
            wallIdY = (checkMap(i, j, map) - 36) / 3;
            clip.x = wallIdX * TILE_SIZE;
            clip.y = wallIdY * TILE_SIZE;
            clip.w = TILE_SIZE;
            clip.h = TILE_SIZE;
            renderer.renderCopy(objects, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
          } else if (checkMap(i, j, map) == 57) {
            renderer.setRenderDrawColor(0, 0, 0, 255);
            renderer.renderDrawRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, TILE_SIZE, TILE_SIZE);
          } else if (checkMap(i, j, map) == 58) {
            renderer.setRenderDrawColor(0, 255, 0, 255);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, ((j-scrollY)*TILE_SIZE) + 28, 8, 8);
          } else if (checkMap(i, j, map) == 59) {
            clip.x = 128;
            clip.y = 704;
            clip.w = 64;
            clip.h = 64;

            renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
            renderer.setRenderDrawColor(212, 175, 55, 255);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, (j-scrollY)*TILE_SIZE+28, 8, 8);
          } else if (checkMap(i, j, map) == 60) {
            clip.x = 128;
            clip.y = 704;
            clip.w = 64;
            clip.h = 64;

            renderer.renderCopy(walls, &clip, ((i-scrollX)*TILE_SIZE) + MENU_OFFSET, (j-scrollY)*TILE_SIZE, 1, 1);
            renderer.setRenderDrawColor(0, 173, 238, 255);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, (j-scrollY)*TILE_SIZE+28, 8, 8);
          } else if (checkMap(i, j, map) == 61) {
            renderer.setRenderDrawColor(205, 133, 63, 255);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET, ((j-scrollY)*TILE_SIZE) + 30, TILE_SIZE, 4);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, ((j-scrollY)*TILE_SIZE) + 28, 8, 8);
          } else if (checkMap(i, j, map) == 62) {
            renderer.setRenderDrawColor(205, 133, 63, 255);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 30, ((j-scrollY)*TILE_SIZE), 4, TILE_SIZE);
            renderer.renderFillRect(((i-scrollX)*TILE_SIZE) + MENU_OFFSET + 28, ((j-scrollY)*TILE_SIZE) + 28, 8, 8);
          }
        }
      }

      SDL_Rect clipMenuWalls;
      SDL_Rect clipMenuObjects;

      renderer.setRenderDrawColor(100, 100, 100, 255);
      renderer.renderFillRect(0, 0, MENU_OFFSET, SCREEN_HEIGHT);

      if (menuScrollX == 0) {
        clipMenuWalls.x = 0;
        clipMenuWalls.y = 0;
        clipMenuWalls.w = 192;
        clipMenuWalls.h = 576;

        renderer.renderCopy(walls, &clipMenuWalls, 0, 64, 1, 1);

        if (IDScrollOffset == 0) {
          wallIdX = (action - (IDScrollOffset * 27)) % 3;
          wallIdY = (action - wallIdX - (IDScrollOffset * 27)) / 3;

          renderer.setRenderDrawColor(255, 165, 0, 255);
          renderer.renderDrawRect(wallIdX * 64, (wallIdY * 64) + 64, 64, 64);
        }
      } else if (menuScrollX == 1) {
        clipMenuWalls.x = 0;
        clipMenuWalls.y = 576;
        clipMenuWalls.w = 192;
        clipMenuWalls.h = 192;

        renderer.renderCopy(walls, &clipMenuWalls, 0, 64, 1, 1);

        clipMenuObjects.x = 0;
        clipMenuObjects.y = 0;
        clipMenuObjects.w = 192;
        clipMenuObjects.h = 384;

        renderer.renderCopy(objects, &clipMenuObjects, 0, 256, 1, 1);

        if (IDScrollOffset == 1) {
          wallIdX = (action - (IDScrollOffset * 27)) % 3;
          wallIdY = (action - wallIdX - (IDScrollOffset * 27)) / 3;

          renderer.setRenderDrawColor(255, 165, 0, 255);
          renderer.renderDrawRect(wallIdX * 64, (wallIdY * 64) + 64, 64, 64);
        }
      } else if (menuScrollX == 2) {
        clipMenuObjects.x = 0;
        clipMenuObjects.y = 384;
        clipMenuObjects.w = 192;
        clipMenuObjects.h = 64;

        renderer.renderCopy(objects, &clipMenuObjects, 0, 64, 1, 1);

        renderer.setRenderDrawColor(255, 255, 255, 255);
        renderer.renderFillRect(0, 128, 64, 64);

        renderer.setRenderDrawColor(0, 255, 0, 255);
        renderer.renderFillRect(28+64, 128+28, 8, 8);

        clipMenuWalls.x = 128;
        clipMenuWalls.y = 704;
        clipMenuWalls.w = 64;
        clipMenuWalls.h = 64;

        renderer.renderCopy(walls, &clipMenuWalls, 128, 128, 1, 1);
        renderer.setRenderDrawColor(212, 175, 55, 255);
        renderer.renderFillRect(28+128, 128+28, 8, 8);

        renderer.renderCopy(walls, &clipMenuWalls, 0, 192, 1, 1);
        renderer.setRenderDrawColor(0, 173, 238, 255);
        renderer.renderFillRect(28, 192+28, 8, 8);

        renderer.setRenderDrawColor(205, 133, 63, 255);
        renderer.renderFillRect(64, 192+30, 64, 4);
        renderer.renderFillRect(64+28, 192+28, 8, 8);

        renderer.setRenderDrawColor(205, 133, 63, 255);
        renderer.renderFillRect(128+30, 192, 4, 64);
        renderer.renderFillRect(128+28, 192+28, 8, 8);

        if (IDScrollOffset == 2) {
          wallIdX = (action - (IDScrollOffset * 27)) % 3;
          wallIdY = (action - wallIdX - (IDScrollOffset * 27)) / 3;

          renderer.setRenderDrawColor(255, 165, 0, 255);
          renderer.renderDrawRect(wallIdX * 64, (wallIdY * 64) + 64, 64, 64);
        }
      }

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
