#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "SDLWrappers/SdlFont.h"
#include "constants.h"
#include "menu_ui.h"

void Menu_ui::drawMenu(SdlRenderer& renderer, SdlTexture& walls,
  SdlTexture& objects, SdlFont& font, bool renderText, int action, int menuScrollX,
  std::string inputText, int realWidth, int IDScrollOffset) {
  SDL_Rect clipMenuWalls;
  SDL_Rect clipMenuObjects;

  SdlTexture tx_load_button(renderer, font, "Load", 255, 255, 255);
  SdlTexture tx_save_button(renderer, font, "Save", 255, 255, 255);

  SdlFont text_font("fonts/wolfenstein.ttf", 24);

  int wallIdX;
  int wallIdY;

  renderer.setRenderDrawColor(100, 100, 100, 255);
  renderer.renderFillRect(0, 0, MENU_OFFSET, SCREEN_HEIGHT);

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

  if (renderText) {
    if (inputText == "") inputText = " ";
    SdlTexture tx_inputText(renderer, text_font, inputText, 255, 255, 255);
    renderer.setRenderDrawColor(100, 100, 100, 255);
    renderer.renderFillRect((realWidth/2)-128, (SCREEN_HEIGHT/2)-16, 256, 32);
    renderer.renderCopyCentered(tx_inputText, NULL,
    (realWidth/2), (SCREEN_HEIGHT/2));
  }
}
