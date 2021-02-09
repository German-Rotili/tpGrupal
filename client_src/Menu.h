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
#include "client_helper.h"
class Menu {
 private:
  Client & client;

public:

  Menu(Client & client);
  ~Menu();

  void runInsertUsername(SdlRenderer& renderer, ClientSettings& settings);

  void runStartPage(SdlRenderer& renderer, ClientSettings& settings);

  void runGameList(SdlRenderer& renderer, ClientSettings& settings);

  void runGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator);

  void runEndScreen(SdlRenderer& renderer, ClientSettings& settings);

  void drawInsertUsername(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText);

  void drawStartPage(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText);

  void drawGameList(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText, std::vector<std::string> matches_id);

  void drawGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator, std::vector<std::string> usernames);

  void drawEndScreen(SdlRenderer& renderer, ClientSettings& settings);

  void textPrompt(SdlRenderer& renderer, ClientSettings& settings, std::string inputText);
};
#endif /* MENU */
