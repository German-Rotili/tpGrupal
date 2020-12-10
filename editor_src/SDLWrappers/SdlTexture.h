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
		SdlTexture(std::string path, const class SdlRenderer& renderer);
		~SdlTexture();

		int getWidth();
		int getHeight();
};

#endif  // SDLTEXTURE_H
