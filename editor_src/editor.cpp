#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 640

int worldMap[10][10] =
                    {
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    };

bool mapHasWall(int x, int y) {
  if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;
  return (worldMap[y][x] == 1);
}

int checkMap(int x, int y) {
  if (x < 0 || x >= 10 || y < 0 || y >= 10) return 0;
  return worldMap[y][x];
}

void toggleTile(int x, int y, int action) {
  worldMap[y][x] = action;
}

int main(int argc, char* args[]) {
  try {
    SdlContexto contexto;  // Inicializa SDL y SDL_image

    SdlWindow window("Wolfenstein_Editor", SCREEN_WIDTH, SCREEN_HEIGHT);

    SdlRenderer renderer = window.getRenderer();

    int playerx = SCREEN_WIDTH/2;
    int playery = SCREEN_HEIGHT/2;

    double actorX = 1;
    double actorY = 4;

    int action = 0;

    //SdlTexture walls("textures/walls.png", renderer);

    bool quit = false;
    SDL_Event e;
    // Main (o game) Loop
    while (!quit) {
      // Event Loop
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_w:
            action = 1;
            break;

            case SDLK_q:
            action = 2;
            break;

            case SDLK_e:
            action = 0;
            break;
          }
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
          if (e.button.button == SDL_BUTTON_LEFT) {
            if (e.button.x > 128) {
              int x = int((e.button.x - 128) / 64);
              int y = int(e.button.y / 64);
              toggleTile(x, y, action);
            }
          }
        }
      }

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderClear();
      int start = 0;
      // Dibujar mapa
      for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
          if (checkMap(i, j) == 1) {
            renderer.setRenderDrawColor(255, 100, 100, 255);
            renderer.renderFillRect((i*64) + 128, j*64, 64, 64);
          }
          renderer.setRenderDrawColor(0, 0, 0, 255);
          renderer.renderDrawRect((i*64) + 128, j*64, 64, 64);
          if (checkMap(i, j) == 2) {
            renderer.setRenderDrawColor(0, 255, 0, 255);
            renderer.renderFillRect((i*64) + 156, (j*64) + 28, 8, 8);
          }
        }
      }

      SDL_Rect clip;
      clip.x = 0;
      clip.y = 0;
      clip.w = 64;
      clip.h = 64;

      clip.x = 0;
      clip.y = 0;
      clip.w = 64;
      clip.h = 64;

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
