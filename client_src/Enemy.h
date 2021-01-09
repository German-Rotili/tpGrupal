#ifndef ENEMY_H
#define ENEMY_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "ZRenderable.h"
class Enemy : public ZRenderable {
	double direction;
	double playerDirection;
	const SdlTexture& sDown;
	const SdlTexture& sDownLeft;
	const SdlTexture& sLeft;
	const SdlTexture& sUpLeft;
	const SdlTexture& sUp;
	const SdlTexture& sShooting;
	const SdlTexture& sDying;
	const double animationSpeed;
	double image_index;
	// int id_weapon;
	public:
		Enemy(double xInicial, double yInicial, SDL_Rect clip, double dirInicial,
			const SdlTexture& sDown, const SdlTexture& sDownLeft,
			const SdlTexture& sLeft, const SdlTexture& sUpLeft,
			const SdlTexture& sUp, const SdlTexture& sShooting, const SdlTexture& sDying,
			ClientSettings& settings);
		~Enemy();
		void setDirections(double newDirection, double newPlayerDirection);
		// void setWeapon(int id_newWeapon);
		void actualizar() override;
};

#endif  // ENEMY_H
