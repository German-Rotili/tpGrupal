#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "../common_src/SDLWrappers/SdlTexture.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "../common_src/SDLWrappers/SdlSound.h"
#include "ZRenderable.h"


class Explosion : public ZRenderable{
	const SdlTexture& texture;
	const SdlSound& sound;
	const int CANT_FRAMES = 9;
	const double ANIMATION_SPEED = 0.4;
	double image_index;
	bool finished;

	public:
		Explosion(double xInicial, double yInicial, SDL_Rect clip, Player& player, SdlTexture& txExplosion, SdlSound& sndExplosion, ClientSettings& settings);
		~Explosion();
		void actualizar() override;
		bool isFinished();
};

#endif  // EXPLOSION_H
