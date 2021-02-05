#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ZRenderable.h"

class Explosion : public ZRenderable{
	const SdlTexture& texture;
	const int CANT_FRAMES = 9;
	const double ANIMATION_SPEED = 0.4;
	double image_index;
	bool finished;

	public:
		Explosion(double xInicial, double yInicial, SDL_Rect clip, const SdlTexture& texture, ClientSettings& settings);
		~Explosion();
		void actualizar() override;
		bool isFinished();
};

#endif  // EXPLOSION_H
