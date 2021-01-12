#ifndef OBJECT_H
#define OBJECT_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ZRenderable.h"

class Object : public ZRenderable{
	const SdlTexture& texture;

	public:
		Object(double xInicial, double yInicial, SDL_Rect clip, const SdlTexture& texture);
		~Object();
		void actualizar() override {};
};

#endif  // OBJECT_H
