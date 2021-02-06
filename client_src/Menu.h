#ifndef MENU
#define MENU
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "SDLWrappers/SdlFont.h"
#include "ClientSettings.h"

class Menu {
public:
  void runStartPage(SdlRenderer& renderer, ClientSettings& settings);

  void runGameLobby(SdlRenderer& renderer, ClientSettings& settings);

  void runEndScreen(SdlRenderer& renderer, ClientSettings& settings);

  void drawStartPage(SdlRenderer& renderer, ClientSettings& settings);

  void drawGameLobby(SdlRenderer& renderer, ClientSettings& settings);

  void drawEndScreen(SdlRenderer& renderer, ClientSettings& settings);
};
#endif /* MENU */
