#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SdlException.h"
#include "SdlRenderer.h"
#include "SdlFont.h"

class SdlTexture {
	friend class SdlRenderer;
	SDL_Texture* texture;
	//Image dimensions
	int width;
	int height;
	public:
		// Constructor por lectura de archivo
		SdlTexture(const class SdlRenderer& renderer, std::string path,
			int r = -1, int g = -1, int b = -1);

		// Constructor usando True Type Fonts
		SdlTexture(const class SdlRenderer& renderer, const class SdlFont& font,
			std::string texto, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

		~SdlTexture();

		void setColorMod(int r, int g, int b);
		int getWidth() const;
		int getHeight() const;
};

#endif  // SDLTEXTURE_H
