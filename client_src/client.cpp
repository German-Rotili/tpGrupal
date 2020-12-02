#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SIZE_NIVEL 5
int worldMap[5][5] = {{ 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {1, 1, 1, 1, 1},
              };

bool hasWall(int posicion) {
  return (posicion == 1);
}

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

    SdlTexture walls("textures/walls.png", renderer);

    int r = 0;
    int g = 255;
    int b = 200;

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
            playery -= 10;
            break;
            case SDLK_LEFT:
            playerx -= 10;
            break;
            case SDLK_RIGHT:
            playerx += 10;
            break;
            case SDLK_DOWN:
            playery += 10;
            break;
            default:
            b = rand() % 256;
          }
        }
      }

      // El FOV va a venir por configuración

      int screenWidth = SCREEN_WIDTH;
      double FOV = 60;
      double dAngle = FOV / screenWidth;
      int actorX = 1;
      int actorY = 4;
      int x = actorX;
      int y = actorY;
      double actorGlobalX = 1.5;
      double actorGlobalY = 4.5;
      double dirAngle = 45;

      for (int rayNumber = 0; rayNumber < screenWidth; rayNumber++) {
        bool sideWall = false;  // Se fija si es una
                               // pared vertical con respecto al map
        double rayAngle = dirAngle + (rayNumber * dAngle) - FOV/2;

        double xIntercept = actorGlobalX + (actorX - actorGlobalX) +
                     (-(actorY - actorGlobalY))/tan(rayAngle);
        double yIntercept = actorGlobalY + (actorY - actorGlobalY) +
                     (actorX - actorGlobalX)/tan(rayAngle);

        int tileStepX = 1;
        int tileStepY = 1;
        double stepX = 1/tan(rayAngle);
        double stepY = tan(rayAngle);

        // Distancia de la pared
        double distX, distY;

        // Loopea hasta encontrar pared
        bool wallFound = false;

        printf("%d %d \n", xIntercept, yIntercept);

        if (hasWall(worldMap[actorX][int(yIntercept)]) && !wallFound) {
          sideWall = false;
          wallFound = true;
        } else {
          x += tileStepX;
          yIntercept += stepY;
        }

        if (hasWall(worldMap[int(xIntercept)][actorY]) && !wallFound) {
          sideWall = true;
          wallFound = true;
        } else {
          y += tileStepY;
          xIntercept += stepX;
        }

        while (!wallFound) {
          if (yIntercept < y) {
            sideWall = false;
            if (hasWall(worldMap[x][int(yIntercept)])) {
              wallFound = true;
            } else {
              x += tileStepX;
              yIntercept += stepY;
            }
          } else if (xIntercept < x) {
            sideWall = true;
            if (hasWall(worldMap[int(xIntercept)][y])) {
              wallFound = true;
            } else {
              y += tileStepY;
              xIntercept += stepX;
            }
          }
        }

        // Dependiendo de si es vert u hori que distancias agarro
        if (sideWall) {
          distX = xIntercept - actorX;
          distY = y - actorY;
        } else {
          distX = x - actorX;
          distY = yIntercept- actorY;
        }

        renderer.setRenderDrawColor(r, g, b, 255);
        renderer.renderClear();
        renderer.setRenderDrawColor(0x00, 0x00, 0x00, 0x00);
        renderer.renderDrawLine(actorX * 64, actorY * 64, distX * 64, distY * 64);
        SDL_Delay(1000/10);


        // Distancia proyectada a la camara
        double proy = (distX * cos(rayAngle)) + (distY * sin(rayAngle));
      }



      renderer.setRenderDrawColor(r, g, b, 255);
      //renderer.renderClear();

      //renderer.renderCopy(player, NULL, playerx, playery);

      SDL_Rect clip;
      clip.x = 0;
      clip.y = 0;
      clip.w = 64;
      clip.h = 64;

      //renderer.renderCopy(walls, &clip, 0, 0);

      clip.x = 0;
      clip.y = 0;
      clip.w = 64;
      clip.h = 64;

      //renderer.renderCopy(walls, &clip, horizontex, horizontey, 1, 3);

      // Dibujar linea negra
      renderer.setRenderDrawColor(0x00, 0x00, 0x00, 0x00);
      //renderer.renderDrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
      //

      renderer.renderPresent();

      SDL_Delay(1000/20);  // 20 fps por segundo
    }
  }
  catch (SdlException& e) {
    std::cout << e.what();
  }
  return 0;
}
