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
int worldMap[7][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
                      {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
                      {0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    };

bool mapHasWall(int x, int y) {
  return (worldMap[y][x] == 1);
}

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
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

    double dirAngle = -65;
    int actorX = 0;
    int actorY = 4;
    double actorDX = 0.5;
    double actorDY = 0.5;

    double FOV = 20;

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
            case SDLK_w:
            dirAngle += 2;
            break;

            case SDLK_s:
            dirAngle -= 2;
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
            default:
            b = rand() % 256;
          }
        }
      }

      // El FOV va a venir por configuración

      renderer.setRenderDrawColor(255, 255, 255, 255);
      renderer.renderClear();
      // Dibujar mapa
      for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 7; j++) {
          if (mapHasWall(i, j)) {
            renderer.setRenderDrawColor(255, 100, 100, 255);
            renderer.renderFillRect(i*64, j*64, 64, 64);
          }
          renderer.setRenderDrawColor(0, 0, 0, 255);
          renderer.renderDrawRect(i*64, j*64, 64, 64);
        }
      }

      int screenWidth = SCREEN_WIDTH;
      double dAngle = FOV / screenWidth;

      for (int rayNumber = 0; rayNumber < screenWidth; rayNumber++) {
        int x = actorX;
        int y = actorY;
        double dx = actorDX;
        double dy = actorDY;

        bool sideWall = false;  // Se fija si es una
                               // pared vertical con respecto al map
        double rayAngle = dirAngle + (rayNumber * dAngle) - FOV/2;

        double xStep;
        double yStep;
        double xIntercept;
        double yIntercept;
        int tileStepX;  // (1, -1) para 0 a 90, (-1, 1) para 90 a 180, (-1, -1) para 180 a 270 y (1, 1) para 270 a 360
        int tileStepY;

        if (0 > rayAngle >= -90) {
          xStep = -1/tan(rayAngle * PI/180.0);
          yStep = tan(rayAngle * PI/180.0);
          xIntercept = x + dx + (-dy)/tan(rayAngle * PI/180.0);
          yIntercept = y + dy + dx*tan(rayAngle * PI/180.0);
          tileStepX = 1;  // (1, -1) para 0 a 90, (-1, 1) para 90 a 180, (-1, -1) para 180 a 270 y (1, 1) para 270 a 360
          tileStepY = -1;
        } else if (-90 > rayAngle >= -180) {
          xStep = 1/tan(rayAngle * PI/180.0);
          yStep = tan(rayAngle * PI/180.0);
          xIntercept = x + dx + (-dy)/tan(rayAngle * PI/180.0);
          yIntercept = y + dy + dx*tan(rayAngle * PI/180.0);
          tileStepX = -1;  // (1, -1) para 0 a 90, (-1, 1) para 90 a 180, (-1, -1) para 180 a 270 y (1, 1) para 270 a 360
          tileStepY = -1;
        } else if (-180 > rayAngle >= -270) {

        } else if (-270 > rayAngle >= -360)


        // Distancia de la pared
        double distX, distY;

        // Loopea hasta encontrar pared
        bool wallFoundX = false;
        bool wallFoundY = false;
        for (int i = 0; i <= 8 && !(wallFoundX && wallFoundY) ; i++) {
          if (!wallFoundX) {
            if (mapHasWall(int(xIntercept), y + tileStepY)) {
              wallFoundX = true;
            }
            else{
              //renderer.setRenderDrawColor(100, 255, 100, 255);
              //renderer.renderFillRect(int(xIntercept)*64, (y+tileStepY)*64, 64, 64);

              y += tileStepY;
              xIntercept += xStep;
            }
          }
          if (!wallFoundY) {
            if (mapHasWall(x+tileStepX, int(yIntercept))) {
              wallFoundY = true;
            }
            else{
              //renderer.setRenderDrawColor(100, 100, 255, 255);
              //renderer.renderFillRect((x+tileStepX)*64, int(yIntercept)*64, 64, 64);

              x += tileStepX;
              yIntercept += yStep;
            }
          }
        }
        //if ((xIntercept * cos(rayAngle * PI/180)) < (x * cos(rayAngle * PI/180))) sideWall = true;
        double d1 = distance(actorX+actorDX, actorY+actorDY, xIntercept, y);
        double d2 = distance(actorX+actorDX, actorY+actorDY, x+tileStepX, yIntercept);

        if (wallFoundX || wallFoundY){
          renderer.setRenderDrawColor(100, 100, 100, 255);
          if (d1 < d2) {

            //renderer.renderFillRect(int(xIntercept)*64, (y+tileStepY)*64, 64, 64);
            renderer.renderDrawLine((actorX+actorDX)*64 , (actorY+actorDY)*64, xIntercept*64 , y*64);


          } else {
            //renderer.renderFillRect((x+tileStepX)*64, int(yIntercept)*64, 64, 64);
            renderer.renderDrawLine((actorX+actorDX)*64 , (actorY+actorDY)*64, (x+tileStepX)*64 , (yIntercept)*64);

          }
        }
        //Lineas interseccion eje horizontal
        renderer.setRenderDrawColor(0, 0, 0, 0xFF);
        //renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY) * 64, (actorX+actorDX- dy/tan(rayAngle*PI/180)) * 64, (actorY+actorDY) * 64);
        //renderer.renderDrawLine((actorX+actorDX - dy/tan(rayAngle*PI/180)) * 64, (actorY+actorDY) * 64, (actorX+actorDX- dy/tan(rayAngle*PI/180)) * 64, (actorY) * 64);

        //renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY) * 64, (actorX+actorDX- dy/tan(rayAngle*PI/180) - 1/tan(rayAngle*PI/180)) * 64, (actorY+actorDY) * 64);
        //renderer.renderDrawLine((actorX+actorDX - (dy/tan(rayAngle*PI/180)) - 1/tan(rayAngle*PI/180)) * 64, (actorY+actorDY) * 64, (actorX+actorDX- (dy/tan(rayAngle*PI/180)) - 1/tan(rayAngle*PI/180)) * 64, (actorY - 1) * 64);

        //Lineas interseccion eje vertical
        //renderer.setRenderDrawColor(100, 30, 100, 0xFF);
        //renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY) * 64, (actorX+actorDX) * 64, (actorY+actorDY + dx*tan(rayAngle*PI/180)) * 64);
        //renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY + dx*tan(rayAngle*PI/180)) * 64, (actorX+actorDX+actorDX) * 64, (actorY+actorDY + dx*tan(rayAngle*PI/180)) * 64);

        //renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY) * 64, (actorX+actorDX) * 64, (actorY+actorDY + dx*tan(rayAngle*PI/180) + tan(rayAngle*PI/180)) * 64);
        //renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY + dx*tan(rayAngle*PI/180) + tan(rayAngle*PI/180)) * 64, (actorX+actorDX+actorDX + 1) * 64, (actorY+actorDY + dx*tan(rayAngle*PI/180) + tan(rayAngle*PI/180)) * 64);

          //Dependiendo de si es vert u hori que distancias agarro
        /*if (!sideWall) {
          distX = (xIntercept - (actorX+actorDX)) * cos(rayAngle*PI/180);
          distY = (xIntercept - (actorY+actorDY)) * sin(rayAngle*PI/180);
        } else {
          printf("esta corriendo esto\n");
          distX = (yIntercept - (actorY+actorDY)) * cos(rayAngle*PI/180);
          distY = (yIntercept - (actorY+actorDY)) * sin(rayAngle*PI/180);
        }
        printf("%f %f \n", xIntercept, yIntercept);*/

      /*renderer.setRenderDrawColor(0x00, 0x00, 0x00, 0x00);
        renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY) * 64, xIntercept * 64, yIntercept * 64);
        renderer.setRenderDrawColor(0x00, 0xFF, 0x00, 0x00);
        renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY) * 64, x * 64, y * 64);
        */

        //renderer.setRenderDrawColor(0x00, 0x00, 0x00, 0x00);
        //renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY) * 64, (actorX+actorDX+distX) * 64, (actorY+actorDY+distY) * 64);

        renderer.setRenderDrawColor(0xFF, 0x00, 0x00, 0x00);
        renderer.renderDrawLine((actorX) * 64, (actorY+actorDY) * 64, (actorX+actorDX) * 64, (actorY+actorDY) * 64);
        renderer.renderDrawLine((actorX+actorDX) * 64, (actorY) * 64, (actorX+actorDX) * 64, (actorY+actorDY) * 64);



        //renderer.setRenderDrawColor(0, 0, 0xFF, 0xFF);
        //renderer.renderDrawPoint(xIntercept*64, actorY+actorDY);
        //renderer.renderDrawPoint(actorX+actorDX, yIntercept*64);



        //renderer.renderPresent();
        //SDL_Delay(1);


        // Distancia proyectada a la camara
        //double proy = (distX * cos(rayAngle * PI/180)) + (distY * sin(rayAngle * PI/180));
      }

      renderer.setRenderDrawColor(0, 0xFF, 0x00, 0x00);
      //renderer.renderDrawLine((actorX+actorDX) * 64, (actorY+actorDY) * 64, (actorX+actorDX+cos(dirAngle*PI/180) * 10) * 64, (actorY+actorDY+sin(dirAngle*PI/180) * 10) * 64);



      //renderer.setRenderDrawColor(r, g, b, 255);


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
      //renderer.setRenderDrawColor(0x00, 0x00, 0x00, 0x00);
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
