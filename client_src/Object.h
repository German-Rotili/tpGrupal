#ifndef OBJECT_H
#define OBJECT_H

#include "../common_src/SDLWrappers/SdlTexture.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "ZRenderable.h"

class Object : public ZRenderable{
	const SdlTexture& texture;

	public:
		Object(double xInicial, double yInicial, SDL_Rect clip, const SdlTexture& texture, Player& player, ClientSettings& settings);
		~Object();
		void actualizar() override {};
};

#endif  // OBJECT_H
