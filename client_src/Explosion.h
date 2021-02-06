#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlSound.h"
#include "ZRenderable.h"
#include "ResourcesLoader.h"


class Explosion : public ZRenderable{
	const SdlTexture& texture;
	const SdlSound& sound;
	const int CANT_FRAMES = 9;
	const double ANIMATION_SPEED = 0.4;
	double image_index;
	bool finished;

	public:
		Explosion(double xInicial, double yInicial, SDL_Rect clip, Player& player, ResourcesLoader& rc, ClientSettings& settings);
		~Explosion();
		void actualizar() override;
		bool isFinished();
};

#endif  // EXPLOSION_H
