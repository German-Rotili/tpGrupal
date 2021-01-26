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


    

    std::string map = client.client_receive_string();
    World world(renderer, settings, map);


    
    //World world(renderer, settings);



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
        // Intencion de moverse adelante
        playerX += playerMovementSpeed*cos(playerAngle*M_PI/180);
        playerY += playerMovementSpeed*sin(playerAngle*M_PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_S]) {
        // Intencion de moverse hacia atras
        playerX -= playerMovementSpeed*cos(playerAngle*M_PI/180);
        playerY -= playerMovementSpeed*sin(playerAngle*M_PI/180);
      }
      if (currentKeyStates[SDL_SCANCODE_A ]) {
        // Intencion de rotar a la izquierda
        playerAngle -= playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_D ]) {
        // Intencion de rotar a la derecha
        playerAngle += playerRotationSpeed;
      }
      if (currentKeyStates[SDL_SCANCODE_SPACE ]) {
        // intencion de disparo
        playerIsShooting = !playerIsShooting;
      }
      //client.client_send(input);
      //std::cout << "Supuestamente enviado" << std::endl;
      if (playerAngle >= 0) {
        playerAngle -= 360;
      } else if (playerAngle < -360) {
        playerAngle +=360;
      }

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
      //

      world.actualizar(playerX, playerY, playerAngle, playerHealth, playerLives,
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
