#ifndef OBJECT_H
#define OBJECT_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
class Object {
	const SdlTexture& texture;
  SDL_Rect clip;
  double x;
  double y;
	// difAngle guarda la diferencia (de grados) entre el angulo que
	// mira el jugador y el angulo desde el x,y del jugador hasta el x,y del objeto
	double difAngle;
	// distToPlayer guarda la distancia
	double distToPlayer;

	double getDifAngle();
	void setDifAngle(double actorX, double actorY, double dirAngle);
	public:
		Object(const SdlTexture& texture,
       SDL_Rect clip, double xInicial, double yInicial);
		~Object();
		double getX();
		double getY();
		double getDistToPlayer();
    void setPosicion(double x, double y);
		bool esVisibleDesde(double actorX, double actorY, double actorDirection, ClientSettings& settings);
    void renderizar(SdlRenderer& renderer,
		 double zBuffer[], ClientSettings& settings);
};

#endif  // OBJECT_H
