#include <stdio.h>
#include <unistd.h>  // Para usleep
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlFont.h"
#include "Player.h"
#include "Object.h"
#include "ClientSettings.h"
#include "rayCaster.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define FPS 30
#define FOV 61

bool compareDistances(Object* o1, Object* o2) {
    return (o1->getDistToPlayer() > o2->getDistToPlayer());
}

int main(int argc, char* args[]) {
  try {
    ClientSettings settings(SCREEN_WIDTH, SCREEN_HEIGHT, FPS, FOV);
    SdlContexto contexto;  // Inicializa SDL y SDL_image

    SdlWindow window("nombre", settings.screenWidth, settings.screenHeight);

    SdlRenderer renderer = window.getRenderer();

    SdlFont font("fonts/wolfenstein.ttf", 50);

    SdlTexture tx_player(renderer, "textures/player.png", 152, 0, 136);
    SdlTexture tx_objects(renderer, "textures/objects.png", 152, 0, 136);
    SdlTexture tx_walls(renderer, "textures/walls.png");

    Player jugador(tx_player, 1.5, 2.5, -45, 100);

    SDL_Rect lamp_clip = {(64+1)*1, (64+1)*3, 64, 64};
    SDL_Rect barrel_clip = {(64+1)*3, (64+1)*0, 64, 64};
    SDL_Rect statue_clip = {(64+1)*3, (64+1)*3, 64, 64};

    std::vector<Object*> objetos;

    objetos.push_back(new Object(tx_objects, barrel_clip, 2.5, 3.5));

    objetos.push_back(new Object(tx_objects, statue_clip, 1.5, 1.5));
    objetos.push_back(new Object(tx_objects, statue_clip, 1.5, 5.5));
    objetos.push_back(new Object(tx_objects, statue_clip, 4.5, 1.5));
    objetos.push_back(new Object(tx_objects, statue_clip, 4.5, 5.5));

    objetos.push_back(new Object(tx_objects, lamp_clip, 5.5, 4));
    objetos.push_back(new Object(tx_objects, lamp_clip, 7, 4));

    // Provisorio hasta que haya comunicacion con el server
    float playerMovementSpeed = float(1) /15;
    float playerRotationSpeed = 3;
    float actorAngle = jugador.getDirection();
    float actorX = jugador.getX();
    float actorY = jugador.getY();
    float actorHealth = 100;
    int actorArmaActual = 0;
    //

    SdlTexture tx_health(renderer, font, std::to_string(int(actorHealth)), 100, 255, 100);

    double zBuffer[SCREEN_WIDTH];
    bool threeD = false;

    bool quit = false;
    SDL_Event e;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    // Main (o game) Loop
    while (!quit) {
      std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

      // Event Loop
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_1:
            jugador.actualizarArmaActual(0);
            break;

            case SDLK_2:
            jugador.actualizarArmaActual(1);
            break;

            case SDLK_3:
            jugador.actualizarArmaActual(2);
            break;

            case SDLK_4:
            jugador.actualizarArmaActual(3);
            break;

            case SDLK_z:
            actorX -= playerMovementSpeed*cos((actorAngle+90)*M_PI/180);
            actorY -= playerMovementSpeed*sin((actorAngle+90)*M_PI/180);
            break;

            case SDLK_c:
            actorX += playerMovementSpeed*cos((actorAngle+90)*M_PI/180);
            actorY += playerMovementSpeed*sin((actorAngle+90)*M_PI/180);
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
        // Intencion de moverse adelante
        actorX += playerMovementSpeed*cos(actorAngle*M_PI/180);
        actorY += playerMovementSpeed*sin(actorAngle*M_PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_S]) {
        // Intencion de moverse hacia atras
        actorX -= playerMovementSpeed*cos(actorAngle*M_PI/180);
        actorY -= playerMovementSpeed*sin(actorAngle*M_PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_A ]) {
        // Intencion de rotar a la izquierda
        actorAngle -= playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_D ]) {
        // Intencion de rotar a la derecha
        actorAngle += playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_SPACE ]) {
        // intencion de disparo
        if (!jugador.animarArma)
          jugador.animarArma = true;
      }

      if (actorAngle >= 0) {
        actorAngle -= 360;
      } else if (actorAngle < -360) {
        actorAngle +=360;
      }

      jugador.actualizarPosicion(actorX, actorY);
      jugador.actualizarDireccion(actorAngle);
      jugador.actualizarVida(actorHealth);
      RayCaster rayCaster;

      if (threeD == true) {
        rayCaster.cast3D(renderer, jugador.getX(), jugador.getY(), jugador.getDirection(), tx_walls, zBuffer, settings);
        std::vector<Object*> visibles;

        // obtengo objetos visibles
        for (std::vector<Object*>::iterator it = objetos.begin();
         it!= objetos.end(); ++it) {
          (*it)->actualizarDifAngle(jugador.getX(), jugador.getY(), actorAngle);

         	float absDifAngle = abs((*it)->getDifAngle());
         	if (absDifAngle <= (settings.fov/1)) {
            (*it)->actualizarDistToPlayer(jugador.getX(), jugador.getY(), settings);
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
        rayCaster.cast2D(renderer, jugador.getX(), jugador.getY(), jugador.getDirection(), settings);
      }

      jugador.renderizar(renderer, settings);

      renderer.renderCopy(tx_health, NULL, 50, SCREEN_HEIGHT-75);
      renderer.renderPresent();

      std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

      unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
      //printf("elapsed microseconds: %i \n", elapsed_microseconds);
      usleep(1000000/settings.fps - elapsed_microseconds);
    }


    // borrado de todos los objetos
    for (std::vector<Object*>::iterator it = objetos.begin();
     it!= objetos.end(); ++it) {
      delete *it;
    }

  }
  catch (SdlException& e) {
    printf("Hubo una excepción:\n");
    std::cout << e.what();
  }
  catch (...) {

  }
  return 0;
}
