#include "SdlFont.h"
#include <string>
#include "SdlException.h"
#include "SdlRenderer.h"

SdlFont::SdlFont(std::string path, int size) {
	font = TTF_OpenFont(path.c_str(), size);
	if (font == NULL) {
		char error[BUF_SIZE];
    snprintf(error, sizeof(error),
		 "Unable to load font %s! SDL_ttf Error: %s\n", path.c_str(), TTF_GetError());
		throw SdlException(error);
  }
}
//  const class SdlRenderer& renderer
SdlFont::~SdlFont() {
	if (font != NULL) {
		TTF_CloseFont(font);
  	font = NULL;
	}
}
