#ifndef ZRENDERABLE_H
#define ZRENDERABLE_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
class ZRenderable {
	protected:
	const SdlTexture* currentTexture;
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

	SDL_RendererFlip flipType;

	const double M_PI_180 = M_PI/180;
	const double HALF_SCREENW;
	const double HALF_SCREENH;
	const double HALF_CLIPW;
	const double HALF_CLIPH;
	const double SCREENHEIGHT_CLIPW;


	public:
		ZRenderable(double xInicial, double yInicial, SDL_Rect clip, ClientSettings& settings);
		~ZRenderable();
		double getX();
		double getY();

		bool esVisibleDesde(double actorX, double actorY, double actorDirection, ClientSettings& settings);
		double getDistToPlayer();

		void setPosicion(double x, double y);
		virtual void actualizar() = 0;
		void updateDistToPlayer(double actorX, double actorY, ClientSettings& settings);
    void renderizar(SdlRenderer& renderer,
		 double zBuffer[], ClientSettings& settings);
};

#endif  // ZRenderable_H
