#ifndef MENU_UI
#define MENU_UI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../common_src/SDLWrappers/SdlContext.h"
#include "../common_src/SDLWrappers/SdlWindow.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "../common_src/SDLWrappers/SdlException.h"
#include "../common_src/SDLWrappers/SdlFont.h"
#include "constants.h"

class Menu_ui {
public:
  void drawMenu(SdlRenderer& renderer, SdlTexture& walls,
    SdlTexture& objects, SdlFont& font, bool renderText, int action, int menuScrollX,
    std::string inputText, int realWidth, int IDScrollOffset,
    int sizeStep);
  void getTooltip(int action, SdlRenderer& renderer, SdlFont& font);
};
#endif /* MENU_UI */
