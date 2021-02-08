#ifndef ZRENDERABLE_H
#define ZRENDERABLE_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "Player.h"
class ZRenderable {
	protected:
	const SdlTexture* currentTexture;
  SDL_Rect clip;
  double x;
  double y;

	// Tiene una referencia a player para obtener su posicion y direccion, y así
	// calcular posicion de renderizado o sonidos.
	const Player& player;
	// difAngle guarda la diferencia (de grados) entre el angulo que
	// mira el jugador y el angulo desde el x,y del jugador hasta el x,y del objeto
	double difAnglePlayer;
	// distToPlayer guarda la distancia
	double distToPlayer;

	double getDifAnglePlayer();
	void setDifAnglePlayer();

	SDL_RendererFlip flipType;

	const double M_PI_180 = M_PI/180;
	const double HALF_SCREENW;
	const double HALF_SCREENH;
	const double HALF_CLIPW;
	const double HALF_CLIPH;
	const double SCREENHEIGHT_CLIPW;


	public:
		ZRenderable(double xInicial, double yInicial, SDL_Rect clip, Player& player, ClientSettings& settings);
		~ZRenderable();
		double getX();
		double getY();

		bool esVisiblePorPlayer(ClientSettings& settings);
		double getDistToPlayer();

		// Retorna true si la posicion es distinta a la que tenia antes
		bool setPosicion(double x, double y);
		
		virtual void actualizar() = 0;
		void updateDistToPlayer();
    void renderizar(SdlRenderer& renderer,
		 double zBuffer[], ClientSettings& settings);
};

#endif  // ZRenderable_H
