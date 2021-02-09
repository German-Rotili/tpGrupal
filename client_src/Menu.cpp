#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include "../common_src/SDLWrappers/SdlContexto.h"
#include "../common_src/SDLWrappers/SdlMusic.h"
#include "../common_src/SDLWrappers/SdlWindow.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "../common_src/SDLWrappers/SdlException.h"
#include "../common_src/SDLWrappers/SdlFont.h"
#include "../common_src/MapHandler.h"
#include "Menu.h"
#include "ClientSettings.h"

Menu::Menu(Client & client):client(client){}
Menu::~Menu(){}

void Menu::runInsertUsername(SdlRenderer& renderer, ClientSettings& settings) {

  std::string inputText = "";
  bool renderText = true;

  bool advance = false;
  bool quit = false;
  SDL_Event e;
  //No es el game loop
  while (!quit) {
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
  }

  if (advance) {
    runStartPage(renderer, settings);
  }
}

void Menu::runStartPage(SdlRenderer& renderer, ClientSettings& settings) {

  SdlMusic musicaMenu("../resources/music/menu.mp3");
  musicaMenu.play();


  MapHandler mapHandler;
  std::string inputText = "";
  bool renderText = false;
  bool insertMapName = false;

  bool advance = false;
  bool quit = false;
  SDL_Event e;
  //No es el game loop
  while (!quit) {
    drawStartPage(renderer, settings, inputText, renderText);
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          if (e.button.y >= (settings.screenHeight/2) - 15 && e.button.y <= (settings.screenHeight/2) + 20) {
            if (e.button.x >= (settings.screenWidth/2) - 150 && e.button.x <= (settings.screenWidth/2) - 30){
              insertMapName = true;
              renderText = true;
              //Despues pide un nombre de archivo .yaml y despues de un SDLK_RETURN va al GameLobby
            } else if (e.button.x >= (settings.screenWidth/2) + 30 && e.button.x <= (settings.screenWidth/2) + 150) {
              // Boton de Unirse a Partida
              this->client.join_game();
              advance = true;
              quit = true;
            }
          }
        }
      } else if (e.type == SDL_KEYDOWN && (insertMapName)) {
        switch (e.key.keysym.sym) {
          case SDLK_RETURN:
          //Ejecutar GameLobby y comunicacion con el server
          try {
              std::string filename(inputText);
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

            this->vector_map = mapHandler.readMap(inputText);

          } catch (std::exception const& e) {
            printf("Hubo una excepción: ");
            std::cout << e.what() << "\n";
          }

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
        (insertMapName)) {
        if(!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' ||
        e.text.text[0] == 'C' || e.text.text[0] == 'v' ||
        e.text.text[0] == 'V' ))) {
          inputText += e.text.text;
          renderText = true;
        }
      }
    }
  }

  if (advance) {
    if (renderText) {
      //CHEQUEO MAPA EN EL SERVIDOR
      runGameLobby(renderer, settings, true);
    } else {
      runGameList(renderer, settings);
    }
  }
}

void Menu::runGameList(SdlRenderer& renderer, ClientSettings& settings) {
  std::string inputText = "";
  bool renderText = false;
  bool insertGameCode = false;
  std::vector<std::string> matches_id;
  bool advance = false;
  bool quit = false;
  SDL_Event e;
  //No es el game loop
  while (!quit) {
    drawGameList(renderer, settings, inputText, renderText, matches_id);
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
          if (e.button.y >= (settings.screenHeight/10 * 8) && e.button.y <= (settings.screenHeight/10 * 8) + (settings.screenHeight/16)) {
            if (e.button.x >= (settings.screenWidth/2) - (settings.screenWidth/4) && e.button.x <= (settings.screenWidth/2) + (settings.screenWidth/4)) {
              //Le pide al usuario que introduzca un codigo de partida
              insertGameCode = true;
              renderText = true;
            } else if (e.button.x >= (settings.screenWidth/2) && e.button.x <= (settings.screenWidth/2) + (2*(settings.screenWidth/4))) {
              //Refresh
              matches_id = this->client.get_matches_id();
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
  }

  if (advance) {
    runGameLobby(renderer, settings, false);
  }
}

void Menu::runGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator) {
  bool advance = false;
  bool quit = false;
  std::vector<std::string> usernames;
  SDL_Event e;
  //No es el game loop
  while (!quit) {
    drawGameLobby(renderer, settings, creator, usernames);
    // Event Loop
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT && usernames.size() == 4) {
          if (e.button.y >= (settings.screenHeight/10 * 8) && e.button.y <= (settings.screenHeight/10 * 8) + (settings.screenHeight/16)) {
            if (e.button.x >= (settings.screenWidth/2) - (settings.screenWidth/4) && e.button.x <= (settings.screenWidth/2)) {
              //Inicia el juego
              this->client.start_match();
              quit = true;
              advance = true;
              quit = true;
            } else if (e.button.x >= (settings.screenWidth/2) && e.button.x <= (settings.screenWidth/2) + (2*(settings.screenWidth/4))) {
              usernames = this->client.get_players_username();
            }
          }
        }
      }
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
  }

  if (advance) {
    runInsertUsername(renderer, settings);
  }
}

void Menu::drawInsertUsername(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText) {
  SdlFont font("../resources/fonts/wolfenstein.ttf", 30);
  SdlTexture tx_desc(renderer, font, "Insert Username", 255, 255, 255);

  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  renderer.renderCopyCentered(tx_desc, NULL, (settings.screenWidth/2), (settings.screenHeight/2)-50);

  if (renderText) {
    textPrompt(renderer, settings, inputText);
  }

  renderer.renderPresent();
}

void Menu::drawStartPage(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText) {
  SdlFont font("../resources/fonts/wolfenstein.ttf", 30);
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

  if (renderText) {
    SdlTexture tx_desc(renderer, font, "Insert Map Path", 255, 255, 255);
    renderer.renderCopyCentered(tx_desc, NULL, (settings.screenWidth/2), (settings.screenHeight/2)-50);
    textPrompt(renderer, settings, inputText);
  }

  renderer.renderPresent();
}

void Menu::drawGameList(SdlRenderer& renderer, ClientSettings& settings, std::string inputText, bool renderText, std::vector<std::string> matches_id) {
  SdlFont font("../resources/fonts/wolfenstein.ttf", 30);

  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  for (int i = 1; i <= matches_id.size(); i++) {
    SdlTexture tx_username(renderer, font, matches_id.at(i), 255, 255, 255);
    renderer.renderCopyCentered(tx_username, NULL, (settings.screenWidth/2), (settings.screenHeight/10) * i + (settings.screenHeight/32));
    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10) * i, (settings.screenWidth/2), (settings.screenHeight/16));
  }

  for (int i = 5; i > matches_id.size(); i--) {
    renderer.setRenderDrawColor(150, 150, 150, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10) * i, (settings.screenWidth/2), (settings.screenHeight/16));
  }

  renderer.setRenderDrawColor(255, 255, 255, 255);
  SdlTexture tx_startGame(renderer, font, "Enter Game", 255, 255, 255);
  renderer.renderCopyCentered(tx_startGame, NULL, (settings.screenWidth/2) - (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));

  renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10)*8, (settings.screenWidth/4), (settings.screenHeight/16));

  renderer.setRenderDrawColor(255, 255, 255, 255);
  SdlTexture tx_refresh(renderer, font, "Refresh", 255, 255, 255);
  renderer.renderCopyCentered(tx_refresh, NULL, (settings.screenWidth/2) + (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
  renderer.renderDrawRect((settings.screenWidth/2), (settings.screenHeight/10)*8, (settings.screenWidth/4), (settings.screenHeight/16));

  if (renderText) {
    renderer.setRenderDrawColor(100, 100, 100, 255);
    SdlTexture tx_desc(renderer, font, "Insert Game Code", 255, 255, 255);
    renderer.renderFillRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/2)-100, (settings.screenWidth/2), 75);
    renderer.renderCopyCentered(tx_desc, NULL, (settings.screenWidth/2), (settings.screenHeight/2)-50);
    textPrompt(renderer, settings, inputText);
  }

  renderer.renderPresent();
}

void Menu::drawGameLobby(SdlRenderer& renderer, ClientSettings& settings, bool creator, std::vector<std::string> usernames) {
  SdlFont font("../resources/fonts/wolfenstein.ttf", 30);

  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderClear();

  for (int i = 1; i <= usernames.size(); i++) {
    SdlTexture tx_username(renderer, font, usernames.at(i), 255, 255, 255);
    renderer.renderCopyCentered(tx_username, NULL, (settings.screenWidth/2), (settings.screenHeight/10) * i + (settings.screenHeight/32));
    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10) * i, (settings.screenWidth/2), (settings.screenHeight/16));
  }

  for (int i = 4; i > usernames.size(); i--) {
    renderer.setRenderDrawColor(150, 150, 150, 255);
    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10) * i, (settings.screenWidth/2), (settings.screenHeight/16));
  }

  if (creator) {
    //Si la partida no esta llena el boton de inicio esta oscuro
    if (usernames.size() == 4) {
      renderer.setRenderDrawColor(255, 255, 255, 255);
      SdlTexture tx_startGame(renderer, font, "Start Game", 255, 255, 255);
      renderer.renderCopyCentered(tx_startGame, NULL, (settings.screenWidth/2) - (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
    } else {
      renderer.setRenderDrawColor(150, 150, 150, 255);
      SdlTexture tx_startGame(renderer, font, "Start Game", 150, 150, 150);
      renderer.renderCopyCentered(tx_startGame, NULL, (settings.screenWidth/2) - (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
    }

    renderer.renderDrawRect((settings.screenWidth/2) - (settings.screenWidth/4), (settings.screenHeight/10)*8, (settings.screenWidth/4), (settings.screenHeight/16));
  }

  renderer.setRenderDrawColor(255, 255, 255, 255);
  SdlTexture tx_refresh(renderer, font, "Refresh", 255, 255, 255);
  renderer.renderCopyCentered(tx_refresh, NULL, (settings.screenWidth/2) + (settings.screenWidth/8), (settings.screenHeight/10) * 8 + (settings.screenHeight/32));
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
