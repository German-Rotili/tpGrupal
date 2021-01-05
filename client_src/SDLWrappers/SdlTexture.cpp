#include <string>
#include "SdlTexture.h"

SdlTexture::SdlTexture(const SdlRenderer& renderer,
	std::string path , int r, int g, int b) {
	// Load image at specified path
	SDL_Surface* auxSurface = IMG_Load(path.c_str());
	if(auxSurface == NULL) {
		char error[BUF_SIZE];
    snprintf(error, sizeof(error), "Unable to load image %s!"
		" SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    throw SdlException(error);
	}
	if (r >= 0) {  // Hago que ese color rgb sea transparente
		SDL_SetColorKey(auxSurface, SDL_TRUE, SDL_MapRGB(auxSurface->format, r, g, b));
	}
	// Create texture from surface pixels
	this->texture = SDL_CreateTextureFromSurface(renderer.renderer, auxSurface);
	if (this->texture == NULL) {
		char error[BUF_SIZE];
    snprintf(error, sizeof(error),
		"Error creating texture %s! SDL_GetError: %s\n",
		 path.c_str(), SDL_GetError());
    throw SdlException(error);
	}

	SDL_FreeSurface(auxSurface);
}

// Crear textura de texto usando font
SdlTexture::SdlTexture(const SdlRenderer& renderer,
	const SdlFont& font, std::string texto, Uint8 r, Uint8 g, Uint8 b) {
		SDL_Color textColor = { r, g, b };
		SDL_Surface* textSurface = TTF_RenderText_Solid(font.font, texto.c_str(), textColor);
	  if (textSurface == NULL) {
			char error[BUF_SIZE];
	    snprintf(error, sizeof(error),
			"Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	    throw SdlException(error);
	  }
	  //Create texture from surface pixels
	  this->texture = SDL_CreateTextureFromSurface(renderer.renderer, textSurface );
	  if(this->texture == NULL) {
			char error[BUF_SIZE];
	    snprintf(error, sizeof(error),
			"Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
	    throw SdlException(error);
	  }
	  //Get image dimensions
		this->width = textSurface->w;
		this->height = textSurface->h;

	  //Get rid of old surface
	  SDL_FreeSurface(textSurface);
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
