#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "Object.h"
#include "ClientSettings.h"
#include "rayCaster.h"


#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define FOV 61
#define PI 3.141592653


bool compareDistances(Object* o1, Object* o2) {
    return (o1->getDistToPlayer() > o2->getDistToPlayer());
}


int main(int argc, char* args[]) {
  try {
    ClientSettings settings(SCREEN_WIDTH, SCREEN_HEIGHT, FOV, PI);
    SdlContexto contexto;  // Inicializa SDL y SDL_image

    SdlWindow window("nombre", settings.screenWidth, settings.screenHeight);

    SdlRenderer renderer = window.getRenderer();

    SDL_Rect notShooting_clip = {64+1, 64+1, 64, 64};
    SDL_Rect shooting_clip = {(64+1)*2, 64+1, 64, 64};

    SdlTexture player("textures/player.png", renderer, 152, 0, 136);
    int playerScale = 4;
    double playerInitialX = 1.5;
    double playerInitialY = 2.5;
    double playerInitialAngle = -45;
    double playerMovementSpeed = double(1) /15;
    double playerRotationSpeed = 3;
    bool playerDisparando = false;

    SdlTexture objects("textures/objects.png", renderer, 152, 0, 136);
    SDL_Rect lamp_clip = {(64+1)*1, (64+1)*3, 64, 64};
    SDL_Rect barrel_clip = {(64+1)*3, (64+1)*0, 64, 64};
    SDL_Rect statue_clip = {(64+1)*3, (64+1)*3, 64, 64};

    std::vector<Object*> objetos;

    objetos.push_back(new Object(objects, barrel_clip, 2.5, 3.5));

    objetos.push_back(new Object(objects, statue_clip, 1.5, 1.5));
    objetos.push_back(new Object(objects, statue_clip, 1.5, 5.5));
    objetos.push_back(new Object(objects, statue_clip, 4.5, 1.5));
    objetos.push_back(new Object(objects, statue_clip, 4.5, 5.5));

    objetos.push_back(new Object(objects, lamp_clip, 5.5, 4));
    objetos.push_back(new Object(objects, lamp_clip, 7, 4));

    double dirAngle = -45;
    double actorX = playerInitialX;
    double actorY = playerInitialY;

    SdlTexture walls("textures/walls.png", renderer);

    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderClear();

    double zBuffer[SCREEN_WIDTH];
    bool threeD = false;

    bool quit = false;
    SDL_Event e;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    // Main (o game) Loop
    while (!quit) {
      // Event Loop
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          // borrado de todos los objetos
          for (std::vector<Object*>::iterator it = objetos.begin();
           it!= objetos.end(); ++it) {
            delete *it;
          }
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_q:
            actorX -= playerMovementSpeed*cos((dirAngle+90)*PI/180);
            actorY -= playerMovementSpeed*sin((dirAngle+90)*PI/180);
            break;

            case SDLK_e:
            actorX += playerMovementSpeed*cos((dirAngle+90)*PI/180);
            actorY += playerMovementSpeed*sin((dirAngle+90)*PI/180);
            break;

            case SDLK_p:
            if (threeD == true)
              threeD = false;
            else
              threeD = true;
            break;
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
        rayCaster.cast3D(renderer, dirAngle, actorX, actorY, walls, zBuffer, settings);
        std::vector<Object*> visibles;

        // obtengo objetos visibles
        for (std::vector<Object*>::iterator it = objetos.begin();
         it!= objetos.end(); ++it) {
          (*it)->actualizarDifAngle(actorX, actorY, dirAngle, settings);

         	float absDifAngle = abs((*it)->getDifAngle());
         	if (absDifAngle <= (settings.fov/1)) {
            (*it)->actualizarDistToPlayer(actorX, actorY, settings);
            visibles.push_back((*it));
          }
        }
        // ordeno los visibles de acuerdo a sus distancias
        std::sort(visibles.begin(), visibles.end(), compareDistances);

        // dibujo ordenadamente todos los visibles
        for (std::vector<Object*>::iterator it = visibles.begin();
         it!= visibles.end(); ++it) {
          (*it)->renderizar(renderer, zBuffer, settings);
        }

      } else {
        rayCaster.cast2D(renderer, dirAngle, actorX, actorY, settings);
      }

      if (playerDisparando) {
        renderer.renderCopyCentered(player, &shooting_clip, settings.screenWidth/2 ,settings.screenHeight-32*playerScale,playerScale,playerScale);
      }
      else {
        renderer.renderCopyCentered(player, &notShooting_clip, settings.screenWidth/2 ,settings.screenHeight-32*playerScale,playerScale,playerScale);
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
