#include <cmath>
#include <algorithm>
#include "Explosion.h"

Explosion::Explosion(double xInicial, double yInicial, SDL_Rect clip,
	 Player& player, SdlTexture& txExplosion, SdlSound& sndExplosion, ClientSettings& settings):
		ZRenderable(xInicial, yInicial, clip, player, settings),
		texture(txExplosion),
		sound(sndExplosion),
		image_index(0),
		finished(false) {
			currentTexture = &texture;

			// Reproducir sonido de explosion
			this->setDifAnglePlayer();
			int angulosonido = this->getDifAnglePlayer();
			if (angulosonido < 0) {
				angulosonido += 360;
			}
			sound.playInPosition(-1, 0, angulosonido, std::min(int(player.getDistanceToPoint(x, y) * 22), 255));
}

Explosion::~Explosion() {}

void Explosion::update() {
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
