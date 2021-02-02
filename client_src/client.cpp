#include <stdio.h>
#include <unistd.h>  // Para usleep
#include <iostream>
#include <vector>
#include <chrono>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlFont.h"
#include "World.h"
#include "ClientSettings.h"
#include "client_helper.h"
#include "../common_src/Serializer.h"
#include "ThRequester.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define FPS 30
#define FOV 61
#define HOSTNAME 1
#define SERVICE 2
int main(int argc, char* args[]) {
  try {
    const char* WINDOW_NAME = "Wolfenstein Client";
    const bool FULLSCREEN = false;
    std::string hostname = args[HOSTNAME];
    std::string service = args[SERVICE];
    Client client(service, hostname);


    std::string input;
    const int horizontex = SCREEN_WIDTH/2;
    const int horizontey = SCREEN_HEIGHT/2;
    ClientSettings settings(SCREEN_WIDTH, SCREEN_HEIGHT, FPS, FOV);
    SdlContexto contexto;  // Inicializa SDL, image, ttf y mixer

    SdlWindow window(WINDOW_NAME, settings.screenWidth, settings.screenHeight, FULLSCREEN);

    SdlRenderer renderer = window.getRenderer();

    /*PROCESAMIENTO DEL MAPA RECIBIDO POR SERVIDOR*/
    std::string map = client.client_receive_string();
    MapHandler maphandler;
    std::vector<std::vector<int>> vector_map = maphandler.readMapFromString(map);
    World world(renderer, settings, vector_map);
    /*********************************************/


    // Provisorio hasta que haya comunicacion con el server
    // Info del server
    double playerMovementSpeed = double(1) /15;
    double playerRotationSpeed = 3;
    // Info Player
    double playerAngle = -45;//90;
    double playerX = 2;
    double playerY = 2;
    double playerHealth = 100;
    int playerLives = 3;
    int playerArmaActual = 0;
    int playerScore = 400;
    bool playerIsShooting = false;
    // Info Enemy
    int enemy_id = 0;
    double enemyAngle = -315;
    double enemyX = 2;
    double enemyY = 2;
    int enemyArmaActual = 0;
    bool enemyIsAlive = true;
    bool enemyIsWalking = false;
    bool enemyIsShooting = false;
    // Info env
    bool allDoorsClosed = true;
    //
    player_t player;
    player.player_id = 10;
    player.pos_x = 2;
    player.pos_y = 2;
    player.direction = 90;
    player.ammo = 100;
    player.current_weapon = '0';

    bool quit = false;
    SDL_Event e;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    /*Creamos y corremos el hilo*/
    intention_t intention = { false, false, false, false, false, false, 0 };;
    ThRequester requester(client, intention);
    requester.start();
    /***************************/


    // Main (o game) Loop
    while (!quit) {
      std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
      intention = { false, false, false, false, false, false, 0 };

      // Event Loop
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_1:
            playerArmaActual = 0;
            break;

            case SDLK_2:
            playerArmaActual = 1;
            break;

            case SDLK_3:
            playerArmaActual = 2;
            break;

            case SDLK_4:
            playerArmaActual = 3;
            break;

            case SDLK_5:
            playerArmaActual = 4;
            break;

            case SDLK_e:
            allDoorsClosed = !allDoorsClosed;
            break;

            case SDLK_z:
            playerScore = 500;
            break;

            case SDLK_c:
            playerScore = 1000;
            break;

            case SDLK_r:
            playerHealth -= 5;
            break;

            case SDLK_t:
            playerHealth += 5;
            break;
          }
        }
      }
      if (currentKeyStates[SDL_SCANCODE_W]) {
        intention.up = true;
        // Intencion de moverse adelante
        // player.pos_x += playerMovementSpeed*cos(player.direction*M_PI/180);
        // player.pos_y += playerMovementSpeed*sin(player.direction*M_PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_S]) {
        intention.down = true;
        // Intencion de moverse hacia atras
        // player.pos_x -= playerMovementSpeed*cos(player.direction*M_PI/180);
        // player.pos_y -= playerMovementSpeed*sin(player.direction*M_PI/180);

      }
      if (currentKeyStates[SDL_SCANCODE_A ]) {
        intention.angle_left = true;

        // Intencion de rotar a la izquierda
        // player.direction -= playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_D ]) {
        // Intencion de rotar a la derecha
        // player.direction += playerRotationSpeed;
        intention.angle_right = true;

      }
      if (currentKeyStates[SDL_SCANCODE_SPACE ]) {
        // intencion de disparo
        // playerIsShooting = !playerIsShooting;
        intention.attack = true;
      }

      /*LOGICA DEL SERVER*/
      // if (player.direction >= 0) {
      //   player.direction -= 360;
      // } else if (player.direction < -360) {
      //   player.direction +=360;
      // }
      /******************/



      // Provisorio para testear enemigos
      enemyIsWalking = false;
      enemyArmaActual = playerArmaActual;
      if (currentKeyStates[SDL_SCANCODE_UP]) {
        enemyIsWalking = true;
        enemyX += playerMovementSpeed*cos(enemyAngle*M_PI/180);
        enemyY += playerMovementSpeed*sin(enemyAngle*M_PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_DOWN]) {
        enemyIsWalking = true;
        enemyX -= playerMovementSpeed*cos(enemyAngle*M_PI/180);
        enemyY -= playerMovementSpeed*sin(enemyAngle*M_PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_LEFT ]) {
        enemyAngle -= playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_RIGHT ]) {
        enemyAngle += playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_RCTRL ]) {
        enemyIsShooting = !enemyIsShooting;
      }
      if (currentKeyStates[SDL_SCANCODE_RSHIFT ]) {
        // intencion de disparo
        enemyIsAlive = !enemyIsAlive;
      }
      if (enemyAngle >= 0) {
        enemyAngle -= 360;
      } else if (enemyAngle < -360) {
        enemyAngle +=360;
      }

     requester.get_snapshot(player);
      
      world.actualizar(player.pos_x, player.pos_y, player.direction, playerHealth, playerLives,
        playerArmaActual, playerIsShooting, playerScore,
         enemyAngle,
         enemyX,
         enemyY,
         enemyArmaActual,
         enemyIsAlive,
         enemyIsWalking,
         enemyIsShooting,
         allDoorsClosed);
      world.renderizar(settings);

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

  }
  catch (SdlException& e) {
    printf("Hubo una excepción:\n");
    std::cout << e.what();
  }
  catch (...) {

  }
  return 0;
}
