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
#define MAP_Y 12
#define MAP_X 12

int worldMap[MAP_Y][MAP_X] =
                    {
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    };

int checkMap(int x, int y) {
  if (x < 0 || x >= MAP_X || y < 0 || y >= MAP_Y) return 0;
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
    int scrollY = 0;
    int scrollX = 0;

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
            case SDLK_UP:
            if (scrollY > 0)
              scrollY -= 1;
            break;

            case SDLK_DOWN:
            if (scrollY < MAP_Y - (SCREEN_HEIGHT/64))
              scrollY += 1;
            break;

            case SDLK_LEFT:
            if (scrollX > 0)
              scrollX -= 1;
            break;

            case SDLK_RIGHT:
            if (scrollX < MAP_X - ((SCREEN_WIDTH - 128)/64))
              scrollX += 1;
            break;
          }
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
          if (e.button.button == SDL_BUTTON_LEFT) {
            if (e.button.x > 128) {
              int x = int((e.button.x - 128) / 64);
              int y = int(e.button.y / 64);
              toggleTile(x+scrollX, y+scrollY, action);
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
            }
          }
        }
      }

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderClear();
      int start = 0;
      // Dibujar mapa
      for (int i = scrollX; i < MAP_X; i++) {
        for (int j = scrollY; j < MAP_Y; j++) {
          if (checkMap(i, j) == 1) {
            renderer.setRenderDrawColor(255, 100, 100, 255);
            renderer.renderFillRect(((i-scrollX)*64) + 128, (j-scrollY)*64, 64, 64);
          }
          renderer.setRenderDrawColor(0, 0, 0, 255);
          renderer.renderDrawRect(((i-scrollX)*64) + 128, (j-scrollY)*64, 64, 64);
          if (checkMap(i, j) == 2) {
            renderer.setRenderDrawColor(0, 255, 0, 255);
            renderer.renderFillRect(((i-scrollX)*64) + 156, ((j-scrollY)*64) + 28, 8, 8);
          } else if (checkMap(i, j) == 3) {
            renderer.setRenderDrawColor(205, 133, 63, 255);
            renderer.renderFillRect(((i-scrollX)*64) + 128, ((j-scrollY)*64) + 30, 64, 4);
          }
        }
      }

      renderer.setRenderDrawColor(100, 100, 100, 255);
      renderer.renderFillRect(0, 0, 128, SCREEN_HEIGHT);

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderFillRect(32, SCREEN_HEIGHT/5, 64, 64);

      renderer.setRenderDrawColor(255, 100, 100, 255);
      renderer.renderFillRect(32, 2 * (SCREEN_HEIGHT/5), 64, 64);

      renderer.setRenderDrawColor(0, 255, 0, 255);
      renderer.renderFillRect(62, (3 * (SCREEN_HEIGHT/5)) + 30, 8, 8);

      renderer.setRenderDrawColor(205, 133, 63, 255);
      renderer.renderFillRect(32, 4 * (SCREEN_HEIGHT/5), 64, 4);



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
