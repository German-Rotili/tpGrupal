#include <iostream>
#include <chrono>
#include "../common_src/SDLWrappers/SdlContext.h"
#include "../common_src/SDLWrappers/SdlWindow.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "World.h"
#include "ClientSettings.h"
#include "client_helper.h"
#include "ClientConfigHandler.h"
#include "Menu.h"
#include "Game.h"

#define FPS 30
#define HOSTNAME 1
#define SERVICE 2
int main(int argc, char* args[]) {
  try {
    std::string hostname = args[HOSTNAME];
    std::string service = args[SERVICE];
    Client client(service, hostname);

    ClientConfigHandler config("../resources/config/clientConfig.yaml");
    ClientSettings settings(config.getWidth(), config.getHeight(), FPS, config.getFOV());
    SdlContext sdlContext;

    const char* WINDOW_NAME = "Wolfenstein Client";
    SdlWindow window(WINDOW_NAME, settings.screenWidth, settings.screenHeight, config.getFullscreen());
    SdlRenderer renderer = window.getRenderer();

    /*Lanzamiento del menu de inicio*/
    Menu menu(client, renderer);
    menu.runInsertUsername(renderer, settings);
    /********************************/

    World world(renderer, settings, menu.vector_map);  // settings va a tener un id inválido hasta que se inicie la partida (no importa porque no se inicia partida hasta que el id sea válido)
    Game game(client, world, settings);
    game.loop();
    std::cout << "salgo de scope" << std::endl;
  }
  catch (std::exception const& e) {
    std::cout << "Hubo una excepción:" << std::endl;
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "Error inesperado" << std::endl;
  }
  return 0;
}
