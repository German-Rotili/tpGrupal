#include <cmath>
#include "Object.h"

Object::Object(double xInicial, double yInicial, SDL_Rect clip,
	 const SdlTexture& texture, Player& player, ClientSettings& settings):
	ZRenderable(xInicial, yInicial, clip, player, settings),
		texture(texture) {
			currentTexture = &texture;
}

Object::~Object() {}
