#ifndef SDLFONT_H
#define SDLFONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "SdlException.h"
#include "SdlRenderer.h"

class SdlFont {
	friend class SdlTexture;
  TTF_Font* font;

	public:
		SdlFont(std::string path, int size);
		~SdlFont();
};

#endif  // SDLFONT_H
