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
#include "ThSender.h"
#include "ThRequester.h"
#include "Menu.h"
#include "../common_src/Action.h"
#include <map>

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

    ClientSettings settings(SCREEN_WIDTH, SCREEN_HEIGHT, FPS, FOV);
    SdlContexto contexto;  // Inicializa SDL, image, ttf y mixer

    SdlWindow window(WINDOW_NAME, settings.screenWidth, settings.screenHeight, FULLSCREEN);

    SdlRenderer renderer = window.getRenderer();

    /*Lanzamiento del menu de inicio*/
    Menu menu;
    menu.runStartPage(renderer, settings);
    /********************************/

    //cliente manda username
        //Server guarda username-id. Chequear si existe
        //Server devuelve nuevo id + id de partidas.
    
    
    //



    /*PROCESAMIENTO DEL MAPA RECIBIDO POR SERVIDOR*/
    Client client(service, hostname);
    std::string map = client.client_receive_string();
    MapHandler maphandler;
    std::vector<std::vector<int>> vector_map = maphandler.readMapFromString(map);


    int id = 0;//lo debo recibir del server
    World world(renderer, settings, vector_map, id);
    bool quit = false;
    SDL_Event e;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);



    /*Creamos y corremos los hilos*/
    std::vector<char> intention;
    Snapshot update_snapshot;
    ThRequester requester(client);
    ThSender sender(client, intention);
    requester.start();
    sender.start();
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
            intention.push_back(SDLK_1);
            break;

            case SDLK_2:
            intention.push_back(SDLK_2);
            break;

            case SDLK_3:
            intention.push_back(SDLK_3);
            break;

            case SDLK_4:
            intention.push_back(SDLK_4);
            break;

            case SDLK_5:
            intention.push_back(SDLK_5);
            break;

            case SDLK_e:
            intention.push_back(SDLK_e);
            break;
          }
        }
      }
      if (currentKeyStates[SDL_SCANCODE_W]) {
            intention.push_back(SDL_SCANCODE_W);
      }
      if (currentKeyStates[SDL_SCANCODE_S]) {
            intention.push_back(SDL_SCANCODE_S);
      }
      if (currentKeyStates[SDL_SCANCODE_A ]) {
            intention.push_back(SDL_SCANCODE_A);
      }
      if (currentKeyStates[SDL_SCANCODE_D ]) {
            intention.push_back(SDL_SCANCODE_D);

      }
      if (currentKeyStates[SDL_SCANCODE_SPACE ]) {
            intention.push_back(SDL_SCANCODE_SPACE);
      }

     update_snapshot = requester.get_snapshot();

     world.actualizar(update_snapshot);

     world.renderizar(settings);

      std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

      unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
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
  catch (std::exception const& e) {
    printf("Hubo una excepción:\n");
    std::cout << e.what();
  }
  catch (...) {

  }
  return 0;
}
