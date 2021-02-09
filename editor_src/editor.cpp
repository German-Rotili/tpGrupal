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
#include "../common_src/MapHandler.h"
#include "EditorConfigHandler.h"
#include "map_ui.h"
#include "menu_ui.h"
#include "constants.h"

int main(int argc, char* args[]) {
  try {
    SdlContexto contexto;  // Inicializa SDL y SDL_image

    int realWidth = SCREEN_WIDTH + MENU_OFFSET;

    SdlWindow window("Wolfenstein_Editor", realWidth, SCREEN_HEIGHT);

    SdlRenderer renderer = window.getRenderer();

    SdlTexture walls(renderer, "textures/walls.png");
    SdlTexture objects(renderer, "textures/objects.png", 152, 0 , 136);

    SdlFont font("fonts/wolfenstein.ttf", 30);
    SdlTexture tx_error(renderer, font, "Hubo un Error", 255, 0, 0);

    int action = 0;
    int scrollY = 0;
    int scrollX = 0;
    int menuScrollX = 0;
    int IDScrollOffset = 0;
    int wallIdX = 0;
    int wallIdY = 0;

    std::string inputText = "";
    bool renderText = false;
    bool save = false, load = false;

    std::string path = "config/editorConfig.yaml";
    EditorConfigHandler configHandler;
    configHandler.initConfig(path);
    int mapX = configHandler.getX();
    int mapY = configHandler.getY();
    Map_ui map_ui;
    map_ui.createMap(mapX, mapY);
    Menu_ui menu_ui;
    MapHandler mapHandler;

    //SdlTexture walls("textures/walls.png", renderer);

    bool quit = false;
    SDL_Event e;
    // Main (o game) Loop
    while (!quit) {
      // Event Loop
      try {
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
              if (scrollY < mapY - (SCREEN_HEIGHT/64))
                scrollY += 1;
              break;

              case SDLK_LEFT:
              if (scrollX > 0)
                scrollX -= 1;
              break;

              case SDLK_RIGHT:
              if (scrollX < mapX - ((realWidth - MENU_OFFSET)/64))
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
                mapHandler.emitMap(inputText, map_ui.getMap());
              } else if  (load == true) {
                map_ui.setMap(mapHandler.readMap(inputText));
              }
              renderText = false;
              save = false;
              load = false;
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
          } else if (e.type == SDL_TEXTINPUT &&
            (save == true || load == true)) {
            if(!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' ||
            e.text.text[0] == 'C' || e.text.text[0] == 'v' ||
            e.text.text[0] == 'V' ))) {
              inputText += e.text.text;
              renderText = true;
            }
          } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
              if (e.button.x > MENU_OFFSET) {
                int x = int((e.button.x - MENU_OFFSET) / TILE_SIZE);
                int y = int(e.button.y / TILE_SIZE);
                map_ui.toggleTile(x+scrollX, y+scrollY, action);
              } else if (e.button.y >= 64 && e.button.y <= 640) {
                wallIdX = int(e.button.x / 64);
                wallIdY = int((e.button.y - 64) / 64);
                IDScrollOffset = menuScrollX;
                action = wallIdX + (wallIdY*3);
                action += IDScrollOffset * 27;
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
        renderer.renderClear();

        map_ui.drawMap(renderer, walls, objects, scrollX, scrollY);

        menu_ui.drawMenu(renderer, walls, objects, font, renderText, action,
        menuScrollX, inputText, realWidth, IDScrollOffset);

        renderer.renderPresent();

        SDL_Delay(1000/20);  // 20 fps por segundo
      } catch (std::exception const& e) {
        printf("Hubo una excepción: ");
        std::cout << e.what() << "\n";
      }
    }
  }
  catch (SdlException& e) {
    std::cout << e.what();
  }
  catch (...) {

  }
  return 0;
}
