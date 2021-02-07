#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlMusic.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "SDLWrappers/SdlFont.h"
#include "Menu.h"
#include "ClientSettings.h"

void Menu::runStartPage(SdlRenderer& renderer, ClientSettings& settings) {

  SdlMusic musicaMenu("../resources/music/menu.mp3");
  musicaMenu.play();

  drawStartPage(renderer, settings);

  bool quit = false;
  SDL_Event e;
  //No es el game loop
  while (!quit) {
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          if (e.button.y >= (settings.screenHeight/2) - 15 && e.button.y <= (settings.screenHeight/2) + 20) {
            if (e.button.x >= (settings.screenWidth/2) - 150 && e.button.x <= (settings.screenWidth/2) - 30){
              // Tengo que agregar el tema de poder pasarle un nombre de archivo de mapa
              // Boton de Nueva Partida
            } else if (e.button.x >= (settings.screenWidth/2) + 30 && e.button.x <= (settings.screenWidth/2) + 150) {
              // Boton de Unirse a Partida
            }
          }
        }
      }
    }
  }

}

void Menu::runGameLobby(SdlRenderer& renderer, ClientSettings& settings) {

}

void Menu::runEndScreen(SdlRenderer& renderer, ClientSettings& settings) {

}

void Menu::drawStartPage(SdlRenderer& renderer, ClientSettings& settings) {
  SdlFont font("fonts/wolfenstein.ttf", 30);
  SdlTexture tx_newGame(renderer, font, "New Game", 255, 255, 255);
  SdlTexture tx_joinGame(renderer, font, "Join Game", 255, 255, 255);

  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  renderer.renderCopyCentered(tx_newGame, NULL, (settings.screenWidth/2) - 90, (settings.screenHeight/2));
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderDrawRect((settings.screenWidth/2) - 150, (settings.screenHeight/2) - 15, 120, 35);

  renderer.renderCopyCentered(tx_joinGame, NULL, (settings.screenWidth/2) + 90, (settings.screenHeight/2));
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderDrawRect((settings.screenWidth/2) + 30, (settings.screenHeight/2) - 15, 120, 35);

  renderer.renderPresent();
}

void Menu::drawGameLobby(SdlRenderer& renderer, ClientSettings& settings) {
  SdlFont font("fonts/wolfenstein.ttf", 30);
}

void Menu::drawEndScreen(SdlRenderer& renderer, ClientSettings& settings) {
  SdlFont font("fonts/wolfenstein.ttf", 30);
}
