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
#define PI 3.14

#define SIZE_NIVEL 5
int worldMap[5][5] = {{1, 1, 1, 1, 1},
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

    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderClear();

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
      double FOV = 30;
      double dAngle = FOV / screenWidth;
      int actorX = 2;
      int actorY = 2;
      int x = actorX;
      int y = actorY;
      double actorGlobalX = 0.5;
      double actorGlobalY = 0.5;
      double dirAngle = 45;

      for (int rayNumber = 0; rayNumber < screenWidth; rayNumber++) {
        bool sideWall = false;  // Se fija si es una
                               // pared vertical con respecto al map
        double rayAngle = dirAngle + (rayNumber * dAngle) - FOV/2;

        double xIntercept = actorX + actorGlobalX +
                     (-actorGlobalY)/tan(rayAngle * PI/180.0);
        double yIntercept = actorY + actorGlobalY +
                     actorGlobalX/tan(rayAngle * PI/180.0);

        printf("%i %f \n", rayNumber, rayAngle);
        printf("%f %f \n", xIntercept, yIntercept);

        int tileStepX = 1;
        int tileStepY = -1;
        double stepX = 1/tan(rayAngle * PI/180.0);
        double stepY = tan(rayAngle * PI/180.0);

        // Distancia de la pared
        double distX, distY;

        // Loopea hasta encontrar pared
        bool wallFound = false;

        if (hasWall(worldMap[x][int(yIntercept)]) && !wallFound) {
          sideWall = false;
          wallFound = true;
        } else {
          x += tileStepX;
          yIntercept += stepY;
        }

        if (hasWall(worldMap[int(xIntercept)][y]) && !wallFound) {
          sideWall = true;
          wallFound = true;
        } else {
          y += tileStepY;
          xIntercept += stepX;
        }


        while (!wallFound) {
          if (yIntercept > y) {
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
          // if (int(yIntercept) > 5 || int(xIntercept) > 5) {
          //   break;
          // }

        }

        // Dependiendo de si es vert u hori que distancias agarro
        if (sideWall) {
          distX = xIntercept - (actorX+actorGlobalX);
          distY = y - (actorY+actorGlobalY);
        } else {
          distX = x - (actorX+actorGlobalX);
          distY = yIntercept- (actorY+actorGlobalY);
        }
        printf("%f %f \n", xIntercept, yIntercept);

        renderer.setRenderDrawColor(255, 255, 255, 255);
        renderer.renderClear();
        renderer.setRenderDrawColor(255, 255, 0, 255);
        for (int i = 0; i < 5; i++) {
          for (int j = 0; j < 5; j++) {
            if (hasWall(worldMap[i][j])) {
              renderer.renderFillRect(i*64, j*64, 64, 64);
            }
          }
        }
        renderer.setRenderDrawColor(0x00, 0x00, 0x00, 0x00);
        renderer.renderDrawLine((actorX+actorGlobalX) * 64, (actorY+actorGlobalY) * 64, (actorX+actorGlobalX+distX) * 64, (actorY+actorGlobalY+distY) * 64);
        renderer.renderPresent();
        SDL_Delay(10);


        // Distancia proyectada a la camara
        double proy = (distX * cos(rayAngle * PI/180)) + (distY * sin(rayAngle * PI/180));
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
