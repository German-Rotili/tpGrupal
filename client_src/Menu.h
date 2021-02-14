#ifndef MENU
#define MENU
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../common_src/SDLWrappers/SdlContexto.h"
#include "../common_src/SDLWrappers/SdlWindow.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "../common_src/SDLWrappers/SdlException.h"
#include "../common_src/SDLWrappers/SdlFont.h"
#include "ClientSettings.h"
#include "client_helper.h"
class Menu {
private:
  Client & client;
  SdlRenderer & renderer;
  SdlFont font;
  SdlTexture tx_refresh;
  SdlTexture tx_startGame_active;
  SdlTexture tx_startGame_inactive;
  SdlTexture tx_newGame;
  SdlTexture tx_joinGame;
  SdlTexture tx_descList;
  SdlTexture tx_enterGame;
  SdlTexture tx_descStart;
  SdlTexture tx_descUser;
public:
  std::vector<std::vector<int>>  vector_map;

  Menu(Client & client, SdlRenderer& renderer);
  ~Menu();

  void runInsertUsername(SdlRenderer& renderer, ClientSettings& settings);

  void runStartPage(SdlRenderer& renderer, ClientSettings& settings);

  void runGameList(SdlRenderer& renderer, ClientSettings& settings);

  void runGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator);

  void runEndScreen(SdlRenderer& renderer, ClientSettings& settings);

  void drawInsertUsername(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText);

  void drawStartPage(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText);

  void drawGameList(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText, std::vector<int> matches_id);

  void drawGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator, std::vector<std::string> usernames);

  void drawEndScreen(SdlRenderer& renderer, ClientSettings& settings);

  void textPrompt(SdlRenderer& renderer, ClientSettings& settings, std::string inputText);
};
#endif /* MENU */
