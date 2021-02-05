#include <cmath>
#include "Explosion.h"

Explosion::Explosion(double xInicial, double yInicial, SDL_Rect clip,
	 const SdlTexture& texture, ClientSettings& settings):
		ZRenderable(xInicial, yInicial, clip, settings),
		texture(texture),
		image_index(0),
		finished(false) {
			currentTexture = &texture;
}

Explosion::~Explosion() {}

void Explosion::actualizar() {
	if (!finished) {
		image_index += ANIMATION_SPEED;
		if (image_index >= CANT_FRAMES) {
			finished = true;
		} else {
			clip.x = 64*int(image_index);
		}
	}
}

bool Explosion::isFinished() {
	return this->finished;
}
