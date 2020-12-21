#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SdlException.h"
#include "SdlRenderer.h"

class SdlTexture {
	friend class SdlRenderer;
	SDL_Texture* texture;
	//Image dimensions
	int width;
	int height;
	public:
		SdlTexture(std::string path, const class SdlRenderer& renderer, int r = -1, int g = -1, int b = -1);
		~SdlTexture();

		void setColorMod(int r, int g, int b);
		int getWidth() const;
		int getHeight() const;
};

#endif  // SDLTEXTURE_H
