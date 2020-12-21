#include <string>
#include "SdlTexture.h"

SdlTexture::SdlTexture(std::string path, const SdlRenderer& renderer, int r, int g, int b) {
	// Load image at specified path
	SDL_Surface* auxSurface = IMG_Load(path.c_str());
	if(auxSurface == NULL) {
		char* error;
    sprintf(error, "Unable to load image %s! SDL_image Error: %s\n",
		 path.c_str(), IMG_GetError());
    throw SdlException(error);
	}
	if (r >= 0) { // Hago que ese color rgb sea transparente
		SDL_SetColorKey(auxSurface, SDL_TRUE, SDL_MapRGB(auxSurface->format, r, g, b));
	}
	// Create texture from surface pixels
	this->texture = SDL_CreateTextureFromSurface(renderer.renderer, auxSurface);
	if (this->texture == NULL) {
		char* error;
    sprintf(error, "Error creating texture %s! SDL_GetError: %s\n",
		 path.c_str(), SDL_GetError());
    throw SdlException(error);
	}
	this->width = auxSurface->w;
	this->height = auxSurface->h;
	SDL_FreeSurface(auxSurface);
}

SdlTexture::~SdlTexture() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

int SdlTexture::getWidth() const {
	return width;
}

int SdlTexture::getHeight() const {
	return height;
}

void SdlTexture::setColorMod(int r, int g, int b) {
	SDL_SetTextureColorMod(texture, r, g, b);
}
