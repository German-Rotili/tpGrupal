#include <cmath>
#include "Object.h"

Object::Object(double xInicial, double yInicial, SDL_Rect clip,
	 const SdlTexture& texture):
	ZRenderable(xInicial, yInicial, clip),
		texture(texture) {
			currentTexture = &texture;
}

Object::~Object() {}
