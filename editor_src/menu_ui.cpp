#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../common_src/SDLWrappers/SdlContext.h"
#include "../common_src/SDLWrappers/SdlWindow.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "../common_src/SDLWrappers/SdlException.h"
#include "../common_src/SDLWrappers/SdlFont.h"
#include "constants.h"
#include "menu_ui.h"

void Menu_ui::drawMenu(SdlRenderer& renderer, SdlTexture& walls,
  SdlTexture& objects, SdlFont& font, bool renderText, int action, int menuScrollX,
  std::string inputText, int realWidth, int IDScrollOffset,
  int sizeStep) {
  SDL_Rect clipMenuWalls;
  SDL_Rect clipMenuObjects;

  SdlTexture tx_load_button(renderer, font, "Load", 255, 255, 255);
  SdlTexture tx_save_button(renderer, font, "Save", 255, 255, 255);
  SdlTexture tx_settings_button(renderer, font, "Size", 255, 255, 255);

  SdlTexture tx_insertX(renderer, font, "Introduzca el tamanio X", 255, 255, 255);
  SdlTexture tx_insertY(renderer, font, "Introduzca el tamanio Y", 255, 255, 255);

  SdlFont text_font("../resources/fonts/wolfenstein.ttf", 24);

  int wallIdX;
  int wallIdY;

  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderFillRect(0, 0, MENU_OFFSET, SCREEN_HEIGHT);
  renderer.renderFillRect(0, SCREEN_HEIGHT, realWidth, FULL_SCREEN_HEIGHT - SCREEN_HEIGHT);

  if (menuScrollX == 0) {
    clipMenuWalls.x = 0;
    clipMenuWalls.y = 0;
    clipMenuWalls.w = 192;
    clipMenuWalls.h = 576;

    renderer.renderCopy(walls, &clipMenuWalls, 0, 64, 1, 1);

    if (IDScrollOffset == 0) {
      wallIdX = (action - (IDScrollOffset * 27)) % 3;
      wallIdY = (action - wallIdX - (IDScrollOffset * 27)) / 3;

      renderer.setRenderDrawColor(255, 165, 0, 255);
      renderer.renderDrawRect(wallIdX * 64, (wallIdY * 64) + 64, 64, 64);
    }
  } else if (menuScrollX == 1) {
    clipMenuWalls.x = 0;
    clipMenuWalls.y = 576;
    clipMenuWalls.w = 192;
    clipMenuWalls.h = 192;

    renderer.renderCopy(walls, &clipMenuWalls, 0, 64, 1, 1);

    clipMenuWalls.x = 64;
    clipMenuWalls.y = 704;
    clipMenuWalls.w = 64;
    clipMenuWalls.h = 64;

    renderer.renderCopy(walls, &clipMenuWalls, 128, 192, 1, 1);

    clipMenuObjects.x = 0;
    clipMenuObjects.y = 0;
    clipMenuObjects.w = 192;
    clipMenuObjects.h = 384;

    renderer.renderCopy(objects, &clipMenuObjects, 0, 256, 1, 1);

    renderer.setRenderDrawColor(205, 133, 63, 255);
    renderer.renderFillRect(64, 192+30, 64, 4);

    renderer.setRenderDrawColor(205, 133, 63, 255);
    renderer.renderFillRect(128+30, 192, 4, 64);

    if (IDScrollOffset == 1) {
      wallIdX = (action - (IDScrollOffset * 27)) % 3;
      wallIdY = (action - wallIdX - (IDScrollOffset * 27)) / 3;

      renderer.setRenderDrawColor(255, 165, 0, 255);
      renderer.renderDrawRect(wallIdX * 64, (wallIdY * 64) + 64, 64, 64);
    }
  } else if (menuScrollX == 2) {
    clipMenuObjects.x = 0;
    clipMenuObjects.y = 384;
    clipMenuObjects.w = 192;
    clipMenuObjects.h = 64;

    renderer.renderCopy(objects, &clipMenuObjects, 0, 64, 1, 1);

    renderer.setRenderDrawColor(255, 255, 255, 255);
    renderer.renderFillRect(0, 128, 64, 64);

    renderer.setRenderDrawColor(0, 255, 0, 255);
    renderer.renderFillRect(28+64, 128+28, 8, 8);

    clipMenuWalls.x = 128;
    clipMenuWalls.y = 704;
    clipMenuWalls.w = 64;
    clipMenuWalls.h = 64;

    renderer.renderCopy(walls, &clipMenuWalls, 128, 128, 1, 1);
    renderer.setRenderDrawColor(212, 175, 55, 255);
    renderer.renderFillRect(28+128, 128+28, 8, 8);
    renderer.renderFillRect(128, 128+30, 64, 4);

    renderer.renderCopy(walls, &clipMenuWalls, 0, 192, 1, 1);
    renderer.setRenderDrawColor(212, 175, 55, 255);
    renderer.renderFillRect(28, 192+28, 8, 8);
    renderer.renderFillRect(30, 192, 4, 64);

    renderer.renderCopy(walls, &clipMenuWalls, 64, 192, 1, 1);
    renderer.setRenderDrawColor(0, 173, 238, 255);
    renderer.renderFillRect(64+28, 192+28, 8, 8);
    renderer.renderFillRect(64, 192+30, 64, 4);

    renderer.renderCopy(walls, &clipMenuWalls, 128, 192, 1, 1);
    renderer.setRenderDrawColor(0, 173, 238, 255);
    renderer.renderFillRect(128+28, 192+28, 8, 8);
    renderer.renderFillRect(128+30, 192, 4, 64);

    renderer.setRenderDrawColor(205, 133, 63, 255);
    renderer.renderFillRect(0, 256+30, 64, 4);
    renderer.renderFillRect(28, 256+28, 8, 8);

    renderer.setRenderDrawColor(205, 133, 63, 255);
    renderer.renderFillRect(64+30, 256, 4, 64);
    renderer.renderFillRect(64+28, 256+28, 8, 8);

    if (IDScrollOffset == 2) {
      wallIdX = (action - (IDScrollOffset * 27)) % 3;
      wallIdY = (action - wallIdX - (IDScrollOffset * 27)) / 3;

      renderer.setRenderDrawColor(255, 165, 0, 255);
      renderer.renderDrawRect(wallIdX * 64, (wallIdY * 64) + 64, 64, 64);
    }
  }

  renderer.renderCopyCentered(tx_save_button, NULL, 30, 20);
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderDrawRect(5, 5, 50, 35);

  renderer.renderCopyCentered(tx_load_button, NULL, 90, 20);
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderDrawRect(65, 5, 50, 35);

  renderer.renderCopyCentered(tx_settings_button, NULL, 150, 20);
  renderer.setRenderDrawColor(255, 255, 255, 255);
  renderer.renderDrawRect(125, 5, 50, 35);

  renderer.renderFillRect(5, 50, 25, 5);
  renderer.renderFillRect(5, 45, 5, 5);

  renderer.renderFillRect(160, 50, 25, 5);
  renderer.renderFillRect(180, 45, 5, 5);

  if (sizeStep == 1) {
    renderer.setRenderDrawColor(100, 100, 100, 255);
    renderer.renderFillRect((realWidth/2)-128, (SCREEN_HEIGHT/2)-66, 256, 32);
    renderer.renderCopyCentered(tx_insertX, NULL, (realWidth/2), (SCREEN_HEIGHT/2) - 50);
  } else if (sizeStep == 2) {
    renderer.setRenderDrawColor(100, 100, 100, 255);
    renderer.renderFillRect((realWidth/2)-128, (SCREEN_HEIGHT/2)-66, 256, 32);
    renderer.renderCopyCentered(tx_insertY, NULL, (realWidth/2), (SCREEN_HEIGHT/2) - 50);
  }

  getTooltip(action, renderer, text_font);

  if (renderText) {
    if (inputText == "") inputText = " ";
    SdlTexture tx_inputText(renderer, text_font, inputText, 255, 255, 255);
    renderer.setRenderDrawColor(100, 100, 100, 255);
    renderer.renderFillRect((realWidth/2)-128, (SCREEN_HEIGHT/2)-16, 256, 32);
    renderer.renderCopyCentered(tx_inputText, NULL,
    (realWidth/2), (SCREEN_HEIGHT/2));
  }
}

void Menu_ui::getTooltip(int action, SdlRenderer& renderer, SdlFont& font) {
  if (action >= 0 && action <= 33) {
    SdlTexture tx_tooltip(renderer, font, "Pared", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action >= 36 && action <= 39) {
    SdlTexture tx_tooltip(renderer, font, "Objeto Bloqueante", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action >= 40 && action <= 43) {
    SdlTexture tx_tooltip(renderer, font, "Objeto No Bloqueante", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 44) {
    SdlTexture tx_tooltip(renderer, font, "Llave Oro", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 45) {
    SdlTexture tx_tooltip(renderer, font, "Llave Cyan", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action >= 46 && action <= 48) {
    SdlTexture tx_tooltip(renderer, font, "Vida", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 49) {
    SdlTexture tx_tooltip(renderer, font, "Municion", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 50) {
    SdlTexture tx_tooltip(renderer, font, "Ametralladora", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 51) {
    SdlTexture tx_tooltip(renderer, font, "Canion de Cadena", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 52) {
    SdlTexture tx_tooltip(renderer, font, "Lanzacohetes", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action >= 53 && action <= 56) {
    SdlTexture tx_tooltip(renderer, font, "Tesoro", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 34) {
    SdlTexture tx_tooltip(renderer, font, "Puerta sin llave Horizontal", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 35) {
    SdlTexture tx_tooltip(renderer, font, "Puerta sin llave Vertical", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 57) {
    SdlTexture tx_tooltip(renderer, font, "Piso", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 58) {
    SdlTexture tx_tooltip(renderer, font, "Spawn de Jugadores", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 59) {
    SdlTexture tx_tooltip(renderer, font, "Puerta llave oro Horizontal", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 60) {
    SdlTexture tx_tooltip(renderer, font, "Puerta llave oro Vertical", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 61) {
    SdlTexture tx_tooltip(renderer, font, "Puerta llave cyan Horizontal", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 62) {
    SdlTexture tx_tooltip(renderer, font, "Puerta llave cyan Vertical", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 63) {
    SdlTexture tx_tooltip(renderer, font, "Puerta secreta Horizontal", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  } else if (action == 64) {
    SdlTexture tx_tooltip(renderer, font, "Puerta secreta Vertical", 255, 255, 0);
    renderer.renderCopy(tx_tooltip, NULL, 2, FULL_SCREEN_HEIGHT-35);
  }
}
