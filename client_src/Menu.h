#ifndef MENU
#define MENU
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../common_src/SDLWrappers/SdlContext.h"
#include "../common_src/SDLWrappers/SdlWindow.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "../common_src/SDLWrappers/SdlException.h"
#include "../common_src/SDLWrappers/SdlFont.h"
#include "ClientSettings.h"
#include "client_helper.h"
#define START 's'
#define REFRESH 'r'

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
  SdlTexture tx_chooseMap;
  SdlTexture tx_descUser;
  SdlTexture tx_descMaps;
  SdlTexture tx_continue;
  SdlMusic music_menu;
public:
  std::vector<std::vector<int>>  vector_map;

  Menu(Client & client, SdlRenderer& renderer);
  ~Menu();

  void runInsertUsername(SdlRenderer& renderer, ClientSettings& settings);

  void runStartPage(SdlRenderer& renderer, ClientSettings& settings);

  void runGameList(SdlRenderer& renderer, ClientSettings& settings);

  void runGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator);

  void runMapSelection(SdlRenderer& renderer, ClientSettings& settings);

  void runEndScreen(SdlRenderer& renderer, ClientSettings& settings);

  void drawInsertUsername(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText);

  void drawStartPage(SdlRenderer& renderer, ClientSettings& settings, std::string inputText);

  void drawGameList(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText, std::vector<int> matches_id);

  void drawGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator, std::vector<std::string> usernames);

  void drawMapSelection(SdlRenderer& renderer, ClientSettings& settings, std::vector<std::string> map_list, int scroll);

  void drawEndScreen(SdlRenderer& renderer, ClientSettings& settings);

  void textPrompt(SdlRenderer& renderer, ClientSettings& settings, std::string inputText);
};
#endif /* MENU */
