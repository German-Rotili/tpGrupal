#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include "../common_src/SDLWrappers/SdlContext.h"
#include "../common_src/SDLWrappers/SdlMusic.h"
#include "../common_src/SDLWrappers/SdlWindow.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "../common_src/SDLWrappers/SdlException.h"
#include "../common_src/SDLWrappers/SdlTexture.h"
#include "../common_src/SDLWrappers/SdlFont.h"
#include "../common_src/MapHandler.h"
#include "Menu.h"
#include "ClientSettings.h"

Menu::Menu(Client & client, SdlRenderer& renderer):client(client),
  renderer(renderer),
  font("../resources/fonts/wolfenstein.ttf", 30),
  tx_refresh(renderer, font, "Refresh", 255, 255, 255),
  tx_startGame_active(renderer, font, "Start Game", 255, 255, 255),
  tx_startGame_inactive(renderer, font, "Start Game", 150, 150, 150),
  tx_newGame(renderer, font, "New Game", 255, 255, 255),
  tx_joinGame(renderer, font, "Join Game", 255, 255, 255),
  tx_descList(renderer, font, "Insert Game Code", 255, 255, 255),
  tx_enterGame(renderer, font, "Enter Game", 255, 255, 255),
  tx_chooseMap(renderer, font, "Choose a map:", 255, 255, 255),
  tx_descUser(renderer, font, "Insert Username", 255, 255, 255),
  tx_descMaps(renderer, font, "Choose a Map", 255, 255, 255),
  tx_continue(renderer, font, "Continue", 255, 255, 255),
  music_menu("../resources/music/menu.mp3") {
    music_menu.play();
  }

Menu::~Menu(){}

void Menu::runInsertUsername(SdlRenderer& renderer, ClientSettings& settings) {
  std::string inputText = "";
  bool renderText = true;

  bool advance = false;
  bool quit = false;
  SDL_Event e;
  //No es el game loop
  while (!quit) {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    drawInsertUsername(renderer, settings, inputText, renderText);
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_RETURN:
            this->client.send_username(inputText);
            advance = true;
            quit = true;
          break;

          case SDLK_BACKSPACE:
          if (inputText.length() > 0) {
            inputText.pop_back();
            renderText = true;
          }
          break;

          case SDLK_c:
          if (SDL_GetModState() & KMOD_CTRL) {
            SDL_SetClipboardText(inputText.c_str());
          }
          break;

          case SDLK_v:
          if (SDL_GetModState() & KMOD_CTRL) {
            inputText = SDL_GetClipboardText();
            renderText = true;
          }
          break;
        }
      } else if (e.type == SDL_TEXTINPUT) {
        if(!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' ||
        e.text.text[0] == 'C' || e.text.text[0] == 'v' ||
        e.text.text[0] == 'V' ))) {
          inputText += e.text.text;
          renderText = true;
        }
      }
    }
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    int sleep_time = 1000000/settings.fps - elapsed_microseconds;
    if (sleep_time > 0) {
      usleep(1000000/settings.fps - elapsed_microseconds);
    } else {
      std::cout << "Bajada de FPS" << std::endl;
    }
  }

  if (advance) {
    runStartPage(renderer, settings);
  }
}

void Menu::runStartPage(SdlRenderer& renderer, ClientSettings& settings) {
  std::string path;
  MapHandler mapHandler;
  std::string inputText = "";
  bool selectMap = false;

  bool advance = false;
  bool quit = false;
  SDL_Event e;
  //No es el game loop
  while (!quit) {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    drawStartPage(renderer, settings, inputText);
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          if (e.button.y >= (settings.screenHeight/2) - 15 && e.button.y <= (settings.screenHeight/2) + 20) {
            if (e.button.x >= (settings.screenWidth/2) - 150 && e.button.x <= (settings.screenWidth/2) - 30){
              selectMap = true;
              advance = true;
              quit = true;
              //Despues pide un nombre de archivo .yaml y despues de un SDLK_RETURN va al GameLobby
            } else if (e.button.x >= (settings.screenWidth/2) + 30 && e.button.x <= (settings.screenWidth/2) + 150) {
              //Join Game
              std::cout << "JOIN" << std::endl;
              this->client.join_game();
              std::cout << "Envio flag de join" << std::endl;

              advance = true;
              quit = true;
            }
          }
        }
      }
    }
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    int sleep_time = 1000000/settings.fps - elapsed_microseconds;
    if (sleep_time > 0) {
      usleep(1000000/settings.fps - elapsed_microseconds);
    } else {
      std::cout << "Bajada de FPS" << std::endl;
    }
  }

  if (advance) {
    if (selectMap) {
      std::cout<<"Ya envie el mapa, me voy al lobby"<<std::endl;
      runMapSelection(renderer, settings);
    } else {
    std::cout <<"Me voy a la lista de espera " <<std::endl;

      runGameList(renderer, settings);
    }
  }
}

void Menu::runMapSelection(SdlRenderer& renderer, ClientSettings& settings) {
   MapHandler mapHandler;

   int boton_apretado = -1;
   std::string path = "";
   bool advance = false;
   bool quit = false;
   SDL_Event e;

  std::vector<std::string> maps = mapHandler.getMapList();

  //No es el game loop
  while (!quit) {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    drawMapSelection(renderer, settings, maps);
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          if (e.button.y >= (settings.screenHeight/8) && e.button.y <= (settings.screenHeight/16 * 10) + (settings.screenHeight/16)) {
            if (e.button.x >= (settings.screenWidth/4) && e.button.x <= (settings.screenWidth/2 + settings.screenWidth/4)) {
             boton_apretado = int(e.button.y/(settings.screenHeight/16)) - 2 ;
             if (boton_apretado >= maps.size()) continue;
             path = "../resources/config/" + maps[boton_apretado] + ".yaml";
             try {
              std::string filename(path);
              std::vector<char> bytes;
              char byte = 0;
              std::ifstream input_file(filename);
              if (!input_file.is_open()) {
                std::cerr << "Error al abrir mapa" << std::endl;
              }
              while (input_file.get(byte)) {
                bytes.push_back(byte);
              }
              input_file.close();

              this->client.new_game(bytes);

              this->vector_map = mapHandler.readMap(maps[boton_apretado]);

           } catch (std::exception const& e) {
              std::cout << "Hubo una excepcion" << std::endl;
              std::cout << e.what() << "\n";
            }
             advance = true;
             quit = true;
            }
          }
        }
      }
    }
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    int sleep_time = 1000000/settings.fps - elapsed_microseconds;
    if (sleep_time > 0) {
      usleep(1000000/settings.fps - elapsed_microseconds);
    } else {
      std::cout << "Bajada de FPS" << std::endl;
    }
  }
  if (advance) {
    runGameLobby(renderer, settings, true);
  }
}

void Menu::runGameList(SdlRenderer& renderer, ClientSettings& settings) {
  std::string inputText = "";
  bool renderText = false;
  bool insertGameCode = false;
  std::vector<int> matches_id;
  bool advance = false;
  bool quit = false;
  SDL_Event e;
  std::cout << "get matches id" << std::endl;

  matches_id = this->client.get_matches_id();
  //No es el game loop
  while (!quit) {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    drawGameList(renderer, settings, inputText, renderText, matches_id);
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          if (e.button.y >= (settings.screenHeight/10 * 8) && e.button.y <= (settings.screenHeight/10 * 8) + (settings.screenHeight/16)) {
            if (e.button.x >= (settings.screenWidth/2) - (settings.screenWidth/4) && e.button.x <= (settings.screenWidth/2)) {
              //Le pide al usuario que introduzca un codigo de partida
              insertGameCode = true;
              renderText = true;
            } else if (e.button.x >= (settings.screenWidth/2) && e.button.x <= (settings.screenWidth/2) + (2*(settings.screenWidth/4))) {
              //Refresh
              std::cout  << "Refreshed asked" << std::endl;
              matches_id = this->client.get_matches_id();
              std::cout  << "Refreshed" << std::endl;

            }
          }
        }
      } else if (e.type == SDL_KEYDOWN && (insertGameCode)) {
        switch (e.key.keysym.sym) {
          case SDLK_RETURN:
          //Ejecutar GameLobby y comunicacion con el server
          this->vector_map = this->client.join_game(inputText);
          advance = true;
          quit = true;
          break;

          case SDLK_BACKSPACE:
          if (inputText.length() > 0) {
            inputText.pop_back();
            renderText = true;
          }
          break;

          case SDLK_c:
          if (SDL_GetModState() & KMOD_CTRL) {
            SDL_SetClipboardText(inputText.c_str());
          }
          break;

          case SDLK_v:
          if (SDL_GetModState() & KMOD_CTRL) {
            inputText = SDL_GetClipboardText();
            renderText = true;
          }
          break;
        }
      } else if (e.type == SDL_TEXTINPUT &&
        (insertGameCode)) {
        if(!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' ||
        e.text.text[0] == 'C' || e.text.text[0] == 'v' ||
        e.text.text[0] == 'V' ))) {
          inputText += e.text.text;
          renderText = true;
        }
      }
    }
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    int sleep_time = 1000000/settings.fps - elapsed_microseconds;
    if (sleep_time > 0) {
      usleep(1000000/settings.fps - elapsed_microseconds);
    } else {
      std::cout << "Bajada de FPS" << std::endl;
    }
  }

  if (advance) {
    runGameLobby(renderer, settings, false);
  }
}

void Menu::runGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator) {
  bool advance = false;
  bool quit = false;

  std::vector<std::string> usernames= this->client.get_players_username();

  SDL_Event e;
  //No es el game loop
  while (!quit) {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    drawGameLobby(renderer, settings, creator, usernames);
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          if (e.button.y >= (settings.screenHeight/10 * 8) && e.button.y <= (settings.screenHeight/10 * 8) + (settings.screenHeight/16)) {
            if (e.button.x >= (settings.screenWidth/2) - (settings.screenWidth/4) && e.button.x <= (settings.screenWidth/2)) {
              //Inicia el juego
              this->client.start_match();
              quit = true;
              advance = true;
              quit = true;
            } else if (e.button.x >= (settings.screenWidth/2) && e.button.x <= (settings.screenWidth/2) + (2*(settings.screenWidth/4))) {
              printf("REFRESH\n");
              this->client.refresh_game();
              usernames = this->client.get_players_username();
            }
          }
        }
      }
    }
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    int sleep_time = 1000000/settings.fps - elapsed_microseconds;
    if (sleep_time > 0) {
      usleep(1000000/settings.fps - elapsed_microseconds);
    } else {
      std::cout << "Bajada de FPS" << std::endl;
    }
  }

  if (advance) {
    //Arranca el juego
  }
}

void Menu::runEndScreen(SdlRenderer& renderer, ClientSettings& settings) {
  bool quit = false;
  bool advance = false;
  SDL_Event e;
  //No es el game loop
  while (!quit) {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    drawEndScreen(renderer, settings);
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_RETURN:
            //Volver al menu ppal y resetear lo necesario
            quit = true;
            advance = true;
          break;
        }
      }
    }
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    int sleep_time = 1000000/settings.fps - elapsed_microseconds;
    if (sleep_time > 0) {
      usleep(1000000/settings.fps - elapsed_microseconds);
    } else {
      std::cout << "Bajada de FPS" << std::endl;
    }
  }

  if (advance) {
    runInsertUsername(renderer, settings);
  }
}

void Menu::drawInsertUsername(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText) {
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  renderer.renderCopyCentered(this->tx_descUser, NULL, (settings.screenWidth/2), (settings.screenHeight/2)-50);

  if (renderText) {
    textPrompt(renderer, settings, inputText);
  }

  renderer.renderPresent();
}

void Menu::drawStartPage(SdlRenderer& renderer, ClientSettings& settings, std::string inputText) {
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  renderer.renderCopyCentered(this->tx_newGame, NULL, (settings.screenWidth/2) - 90, (settings.screenHeight/2));
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderDrawRect((settings.screenWidth/2) - 150, (settings.screenHeight/2) - 15, 120, 35);

  renderer.renderCopyCentered(this->tx_joinGame, NULL, (settings.screenWidth/2) + 90, (settings.screenHeight/2));
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderDrawRect((settings.screenWidth/2) + 30, (settings.screenHeight/2) - 15, 120, 35);

  renderer.renderPresent();
}

void Menu::drawGameList(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText, std::vector<int> matches_id) {
  SdlFont font("../resources/fonts/wolfenstein.ttf", 30);
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  for (int i = 0; i < matches_id.size(); i++) {
    SdlTexture tx_username(renderer, font, std::to_string(matches_id.at(i)), 255, 255, 255);
    renderer.renderCopyCentered(tx_username, NULL, (settings.screenWidth/2), (settings.screenHeight/10) * (i+1) + (settings.screenHeight/32));
    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10) * (i+1), (settings.screenWidth/2), (settings.screenHeight/16));
  }

  for (int i = 5; i > matches_id.size(); i--) {
    renderer.setRenderDrawColor(150, 150, 150, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10) * i, (settings.screenWidth/2), (settings.screenHeight/16));
  }

  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderCopyCentered(this->tx_enterGame, NULL, (settings.screenWidth/2) - (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
  renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10)*8, (settings.screenWidth/4), (settings.screenHeight/16));

  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderCopyCentered(this->tx_refresh, NULL, (settings.screenWidth/2) + (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
  renderer.renderDrawRect((settings.screenWidth/2), (settings.screenHeight/10)*8, (settings.screenWidth/4), (settings.screenHeight/16));

  if (renderText) {
    renderer.setRenderDrawColor(100, 100, 100, 255);
    renderer.renderFillRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/2)-100, (settings.screenWidth/2), 75);
    renderer.renderCopyCentered(this->tx_descList, NULL, (settings.screenWidth/2), (settings.screenHeight/2)-50);
    textPrompt(renderer, settings, inputText);
  }

  renderer.renderPresent();
}

void Menu::drawMapSelection(SdlRenderer& renderer, ClientSettings& settings, std::vector<std::string> map_list) {
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();
  renderer.renderCopyCentered(tx_chooseMap, NULL, settings.screenWidth/2, settings.screenHeight/16);
  // dibujar mensaje de seleccion
  for (int i = 0; i < map_list.size(); i++) {
    if (i >= 10) continue;
    SdlTexture tx_mapname(renderer, font, map_list.at(i), 255, 255, 255);
    renderer.renderCopyCentered(tx_mapname, NULL, (settings.screenWidth/2), (settings.screenHeight/16) * (i+2) + (settings.screenHeight/32));
    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/16) * (i+2), (settings.screenWidth/2), (settings.screenHeight/16));
  }

  for (int i = 10; i > map_list.size(); i--) {
    renderer.setRenderDrawColor(150, 150, 150, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/16) * (i+1), (settings.screenWidth/2), (settings.screenHeight/16));
  }

  renderer.renderPresent();
}

void Menu::drawGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator, std::vector<std::string> usernames) {
  SdlFont font("../resources/fonts/wolfenstein.ttf", 30);
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  for (int i = 0; i < usernames.size(); i++) {
    SdlTexture tx_username(renderer, font, usernames.at(i), 255, 255, 255);
    renderer.renderCopyCentered(tx_username, NULL, (settings.screenWidth/2), (settings.screenHeight/10) * (i+1) + (settings.screenHeight/32));
    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10) * (i+1), (settings.screenWidth/2), (settings.screenHeight/16));
  }

  for (int i = 4; i > usernames.size(); i--) {
    renderer.setRenderDrawColor(150, 150, 150, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10) * i, (settings.screenWidth/2), (settings.screenHeight/16));
  }

  if (creator) {
    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderCopyCentered(this->tx_startGame_active, NULL, (settings.screenWidth/2) - (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));

    //Si la partida no esta llena el boton de inicio esta oscuro
    // if (usernames.size() == 4) {
    //   renderer.setRenderDrawColor(255, 255, 255, 255);
    //
    //   renderer.renderCopyCentered(this->tx_startGame_active, NULL, (settings.screenWidth/2) - (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
    // } else {
    //   renderer.setRenderDrawColor(150, 150, 150, 255);
    //   renderer.renderCopyCentered(this->tx_startGame_inactive, NULL, (settings.screenWidth/2) - (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
    // }

    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10)*8, (settings.screenWidth/4), (settings.screenHeight/16));
  }

  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderCopyCentered(this->tx_refresh, NULL, (settings.screenWidth/2) + (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
  renderer.renderDrawRect((settings.screenWidth/2), (settings.screenHeight/10)*8, (settings.screenWidth/4), (settings.screenHeight/16));

  renderer.renderPresent();
}

void Menu::drawEndScreen(SdlRenderer& renderer, ClientSettings& settings) {
  SdlFont font("../resources/fonts/wolfenstein.ttf", 30);
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  for (int i = 1; i <= 4; i++) {
    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/5) * i, (settings.screenWidth/2), (settings.screenHeight/8));
  }

  for (int i = 1; i<= 4; i++) {
    SdlTexture tx_username(renderer, font, "username", 255, 255, 255);
    renderer.renderCopyCentered(tx_username, NULL, (settings.screenWidth/2), ((settings.screenHeight/5) * i) + (settings.screenHeight/32));
    SdlTexture tx_puntuacion(renderer, font, "puntuacion", 255, 255, 255);
    renderer.renderCopyCentered(tx_puntuacion, NULL, (settings.screenWidth/2), ((settings.screenHeight/5) * i) + (settings.screenHeight/12));
  }

  renderer.renderPresent();
}

void Menu::textPrompt(SdlRenderer& renderer, ClientSettings& settings, std::string inputText) {
  SdlFont text_font("../resources/fonts/wolfenstein.ttf", 24);
  if (inputText == "") inputText = " ";
  SdlTexture tx_inputText(renderer, text_font, inputText, 255, 255, 255);
  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderFillRect((settings.screenWidth/2)-128, (settings.screenHeight/2)-16, 256, 32);
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderDrawRect((settings.screenWidth/2)-128, (settings.screenHeight/2)-16, 256, 32);
  renderer.renderCopyCentered(tx_inputText, NULL,
  (settings.screenWidth/2), (settings.screenHeight/2));
}
