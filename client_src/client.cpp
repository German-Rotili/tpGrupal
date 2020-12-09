#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "rayCaster.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PI 3.14

int main(int argc, char* args[]) {
  try {
    const int horizontex = SCREEN_WIDTH/2;
    const int horizontey = SCREEN_HEIGHT/2;

    SdlContexto contexto;  // Inicializa SDL y SDL_image

    SdlWindow window("nombre", SCREEN_WIDTH, SCREEN_HEIGHT);

    SdlRenderer renderer = window.getRenderer();

    SdlTexture player("flappybird.png", renderer);

    int playerx = SCREEN_WIDTH/2;
    int playery = SCREEN_HEIGHT/2;

    double dirAngle = -230;
    double actorX = 1;
    double actorY = 4;
    double actorDX = 0.5;
    double actorDY = 0.5;

    double FOV = 20;

    SdlTexture walls("textures/walls.png", renderer);

    int r = 0;
    int g = 255;
    int b = 200;

    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderClear();

    bool threeD = false;

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
            dirAngle += 0.5;
            break;

            case SDLK_s:
            dirAngle -= 0.5;
            break;

            case SDLK_a:
            FOV -= 2;
            break;

            case SDLK_d:
            FOV += 2;
            break;

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

            case SDLK_p:
            if (threeD == true) threeD = false;
            else threeD = true;
            break;

            default:
            b = rand() % 256;
          }
        }
      }

      RayCaster rayCaster;

      if (threeD == true) {
        rayCaster.cast3D(&renderer, dirAngle, actorX, actorY, actorDX, actorDY, FOV);
      } else {
        rayCaster.cast2D(&renderer, dirAngle, actorX, actorY, actorDX, actorDY, FOV);
      }

      renderer.setRenderDrawColor(0, 0xFF, 0x00, 0x00);

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
  return 0;
}
