#include <cmath>
#include "Object.h"

Object::Object(double xInicial, double yInicial, SDL_Rect clip,
	 const SdlTexture& texture, ClientSettings& settings):
	ZRenderable(xInicial, yInicial, clip, settings),
		texture(texture) {
			currentTexture = &texture;
}

Object::~Object() {}
