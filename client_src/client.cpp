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


    SDL_Rect clip;
    clip.x = 64+1;
    clip.y = 64+1;
    clip.w = 64;
    clip.h = 64;

    SDL_Rect clip2;
    clip2.x = 64*2 + 2;
    clip2.y = 64+1;
    clip2.w = 64;
    clip2.h = 64;
    SdlTexture player("textures/player.png", renderer);
    int playerScale = 4;
    double playerInitialX = 1.5;
    double playerInitialY = 2.5;
    double playerInitialAngle = -45;
    double playerMovementSpeed = double(1) /20;
    double playerRotationSpeed = 3;
    bool playerDisparando = false;


    double dirAngle = -45;
    double actorX = playerInitialX;
    double actorY = playerInitialY;

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
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    // Main (o game) Loop
    while (!quit) {
      // Event Loop
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_q:
            FOV -= 2;
            break;

            case SDLK_e:
            FOV += 2;
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

      if (currentKeyStates[SDL_SCANCODE_W]) {
        actorX += playerMovementSpeed*cos(dirAngle*PI/180);
        actorY += playerMovementSpeed*sin(dirAngle*PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_S]) {
        actorX -= playerMovementSpeed*cos(dirAngle*PI/180);
        actorY -= playerMovementSpeed*sin(dirAngle*PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_A ]) {
        dirAngle -= playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_D ]) {
        dirAngle += playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_SPACE ]) {
        if (playerDisparando == false) {
          playerDisparando = true;
        } else {
          playerDisparando = false;
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

      if (playerDisparando) {
        renderer.renderCopy(player, &clip2, SCREEN_WIDTH/2 + 64*(2-playerScale),SCREEN_HEIGHT-64*playerScale,playerScale,playerScale);
      }
      else {
        renderer.renderCopy(player, &clip, SCREEN_WIDTH/2 + 64*(2-playerScale),SCREEN_HEIGHT-64*playerScale,playerScale,playerScale);
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
