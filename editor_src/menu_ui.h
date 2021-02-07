#ifndef MENU_UI
#define MENU_UI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SDLWrappers/SdlContexto.h"
#include "SDLWrappers/SdlWindow.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlException.h"
#include "SDLWrappers/SdlFont.h"
#include "constants.h"

class Menu_ui {
public:
  void drawMenu(SdlRenderer& renderer, SdlTexture& walls, SdlTexture& objects, SdlFont& font,
  bool renderText, int action, int menuScrollX,
  std::string inputText, int realWidth, int IDScrollOffset);
};
#endif /* MENU_UI */
