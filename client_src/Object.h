#ifndef OBJECT_H
#define OBJECT_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
class Object {
	const SdlTexture& texture;
  SDL_Rect clip;
  float x;
  float y;
	// difAngle guarda la diferencia entre el angulo que
	// mira el jugador y el angulo desde el x,y del jugador hasta el x,y del objeto
	float difAngle;
	// distToPlayer guarda la distancia
	float distToPlayer;
	public:
		Object(const SdlTexture& texture,
       SDL_Rect clip, float xInicial, float yInicial);
		~Object();
		float getX();
		float getY();
		float getDifAngle();
		float getDistToPlayer();
		void setDifAngle(float actorX, float actorY, float dirAngle);
    void setPosicion(float x, float y);
		void setDistToPlayer(float actorX, float actorY, ClientSettings& settings);
    void renderizar(SdlRenderer& renderer,
		 double zBuffer[], ClientSettings& settings);
};

#endif  // OBJECT_H
