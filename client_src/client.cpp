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
#include "Hud.h"
#include "ZRenderable.h"
#include "Object.h"
#include "Enemy.h"
#include "ClientSettings.h"
#include "rayCaster.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define FPS 30
#define FOV 61

bool compareDistances(ZRenderable* o1, ZRenderable* o2) {
    return (o1->getDistToPlayer() > o2->getDistToPlayer());
}

int main(int argc, char* args[]) {
  try {
    const char* WINDOW_NAME = "Wolfenstein Client";
    const bool FULLSCREEN = false;
    ClientSettings settings(SCREEN_WIDTH, SCREEN_HEIGHT, FPS, FOV);
    SdlContexto contexto;  // Inicializa SDL, image, ttf y mixer

    SdlWindow window(WINDOW_NAME, settings.screenWidth, settings.screenHeight, FULLSCREEN);

    SdlRenderer renderer = window.getRenderer();

    Player jugador(renderer, settings, 1.5, 2.5, -45, 100, 0, 3);

    Hud hud_jugador(renderer, jugador, settings);

    SdlTexture tx_objects(renderer, "textures/objects.png", 152, 0, 136);
    SdlTexture tx_walls(renderer, "textures/walls.png");

    SdlTexture tx_guardDown(renderer, "textures/enemies/guard/down_strip5.png", 152, 0, 136);
    SdlTexture tx_guardDownLeft(renderer, "textures/enemies/guard/downleft_strip5.png", 152, 0, 136);
    SdlTexture tx_guardLeft(renderer, "textures/enemies/guard/left_strip5.png", 152, 0, 136);
    SdlTexture tx_guardUpLeft(renderer, "textures/enemies/guard/upleft_strip5.png", 152, 0, 136);
    SdlTexture tx_guardUp(renderer, "textures/enemies/guard/up_strip5.png", 152, 0, 136);
    SdlTexture tx_guardShooting(renderer, "textures/enemies/guard/shooting_strip3.png", 152, 0, 136);
    SdlTexture tx_guardDying(renderer, "textures/enemies/guard/dying_strip5.png", 152, 0, 136);

    SDL_Rect enemy_clip = {0, 0, 64, 64};

    SDL_Rect lamp_clip = {(64+1)*1, (64+1)*3, 64, 64};
    SDL_Rect barrel_clip = {(64+1)*3, (64+1)*0, 64, 64};
    SDL_Rect statue_clip = {(64+1)*3, (64+1)*3, 64, 64};

    std::vector<ZRenderable*> objetos;

    // Parte de Información inicial del server
    //objetos.push_back(new Object(2.5, 3.5, barrel_clip, tx_objects));
    //objetos.push_back(new Object(1.5, 1.5, statue_clip, tx_objects));
    //objetos.push_back(new Object(1.5, 5.5, statue_clip, tx_objects));
    //objetos.push_back(new Object(4.5, 1.5, statue_clip, tx_objects));
    //objetos.push_back(new Object(4.5, 5.5, statue_clip, tx_objects));
    //objetos.push_back(new Object(5.5, 4.0, lamp_clip, tx_objects));
    //objetos.push_back(new Object(7.0, 4.0, lamp_clip, tx_objects));
    objetos.push_back(new Enemy(2.5, 4.5, enemy_clip, 0, tx_guardDown,
      tx_guardDownLeft, tx_guardLeft, tx_guardUpLeft, tx_guardUp,
      tx_guardShooting, tx_guardDying, settings));




    // Provisorio hasta que haya comunicacion con el server
    double playerMovementSpeed = double(1) /15;
    double playerRotationSpeed = 3;
    double actorAngle = jugador.getDirection();
    double actorX = jugador.getX();
    double actorY = jugador.getY();
    double actorHealth = 100;
    int actorArmaActual = 0;
    //

    double zBuffer[SCREEN_WIDTH];
    bool threeD = true;

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
            jugador.setArmaActual(0);
            break;

            case SDLK_2:
            jugador.setArmaActual(1);
            break;

            case SDLK_3:
            jugador.setArmaActual(2);
            break;

            case SDLK_4:
            jugador.setArmaActual(3);
            break;

            case SDLK_5:
            jugador.setArmaActual(4);
            break;

            case SDLK_z:
            jugador.setScore(500);
            break;

            case SDLK_c:
            jugador.setScore(1000);
            break;

            case SDLK_r:
            actorHealth -= 5;
            break;

            case SDLK_t:
            actorHealth += 5;
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

      jugador.setPosicion(actorX, actorY);
      jugador.setDirection(actorAngle);
      jugador.setHealth(actorHealth);
      // jugador.setScore();
      // jugador.setLives();
      // jugador.setArmaActual();
      // Faltan implementar: Llaves y actualizacion de balas.
      RayCaster rayCaster;

      if (threeD == true) {
        rayCaster.cast3D(renderer, jugador.getX(), jugador.getY(), jugador.getDirection(), tx_walls, zBuffer, settings);
        std::vector<ZRenderable*> visibles;

        // Actualizo direccion de enemigos;
        ((Enemy*) objetos.back())->setDirections(0, jugador.getDirection());

        // obtengo objetos visibles
        for (std::vector<ZRenderable*>::iterator it = objetos.begin();
         it!= objetos.end(); ++it) {
           (*it)->actualizar();
           if ((*it)->esVisibleDesde(jugador.getX(), jugador.getY(), jugador.getDirection(), settings)) {
             (*it)->updateDistToPlayer(jugador.getX(), jugador.getY(), settings);
             visibles.push_back((*it));
          }
        }
        // ordeno los visibles de acuerdo a sus distancias
        std::sort(visibles.begin(), visibles.end(), compareDistances);
        // dibujo ordenadamente todos los visibles
        for (std::vector<ZRenderable*>::iterator it = visibles.begin();
         it!= visibles.end(); ++it) {
          (*it)->renderizar(renderer, zBuffer, settings);
        }

      } else {
        rayCaster.cast2D(renderer, jugador.getX(), jugador.getY(), jugador.getDirection(), settings);
      }

      jugador.renderizar(settings);
      hud_jugador.actualizar();
      hud_jugador.renderizar(settings);
      renderer.renderPresent();

      std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

      unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
      //printf("elapsed microseconds: %i \n", elapsed_microseconds);
      int sleep_time = 1000000/settings.fps - elapsed_microseconds;
      if (sleep_time > 0) {
        usleep(1000000/settings.fps - elapsed_microseconds);
      } else {
        printf("Bajada de FPS\n");
      }
    }

    // borrado de todos los objetos
    for (std::vector<ZRenderable*>::iterator it = objetos.begin();
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
