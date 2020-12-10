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

int worldMap[10][10] = {
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
                      {1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
                      {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
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

void toggleWall(int x, int y) {
  if (mapHasWall(x, y)) worldMap[y][x] = 0;
  else worldMap[y][x] = 1;
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
            actorY -= 1;
            break;
            case SDLK_DOWN:
            actorY += 1;
            break;
            case SDLK_LEFT:
            actorX -= 1;
            break;
            case SDLK_RIGHT:
            actorX += 1;
            break;

            case SDLK_w:
            toggleWall(actorX, actorY);
            break;

            default:
            break;
          }
        }
      }

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderClear();
      // Dibujar mapa
      for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
          if (mapHasWall(i, j)) {
            renderer.setRenderDrawColor(255, 100, 100, 255);
            renderer.renderFillRect((i*64) + 128, j*64, 64, 64);
          }
          renderer.setRenderDrawColor(0, 0, 0, 255);
          renderer.renderDrawRect((i*64) + 128, j*64, 64, 64);
        }
      }
      renderer.renderFillRect((actorX*64) + 158, (actorY*64) + 30, 4, 4);

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
