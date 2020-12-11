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

int main(int argc, char* args[]) {
  try {
    const int horizontex = SCREEN_WIDTH/2;
    const int horizontey = SCREEN_HEIGHT/2;

    SdlContexto contexto;  // Inicializa SDL y SDL_image

    SdlWindow window("nombre", SCREEN_WIDTH, SCREEN_HEIGHT);

    SdlRenderer renderer = window.getRenderer();

    SdlTexture player("flappybird.png", renderer);

    double dirAngle = -45;
    double actorX = 1.5;
    double actorY = 2.5;

    double FOV = 54;

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
            case SDLK_a:
            FOV -= 2;
            break;

            case SDLK_d:
            FOV += 2;
            break;

            case SDLK_UP:
            actorX += cos(dirAngle*PI/180)/32;
            actorY += sin(dirAngle*PI/180)/32;

            break;
            case SDLK_DOWN:
            actorX -= cos(dirAngle*PI/180)/32;
            actorY -= sin(dirAngle*PI/180)/32;
            break;
            case SDLK_LEFT:
            dirAngle -= 2;
            break;
            case SDLK_RIGHT:
            dirAngle += 2;
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

      if (dirAngle >= 0) {
        dirAngle -= 360;
      } else if (dirAngle < -360) {
        dirAngle +=360;
      }

      if (threeD == true) {
        rayCaster.cast3D(renderer, dirAngle, actorX, actorY, FOV, walls);
      } else {
        rayCaster.cast2D(renderer, dirAngle, actorX, actorY, FOV);
      }

      renderer.renderPresent();

      SDL_Delay(1000/30);  // 30 fps por segundo
    }
  }
  catch (SdlException& e) {
    std::cout << e.what();
  }
  catch (...) {

  }
  return 0;
}
