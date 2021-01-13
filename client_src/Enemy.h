#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"

#include "ZRenderable.h"
class Enemy : public ZRenderable {
	double relativeDirection;
	std::vector<const SdlTexture*> sDown;
	std::vector<const SdlTexture*> sDownLeft;
	std::vector<const SdlTexture*> sLeft;
	std::vector<const SdlTexture*> sUpLeft;
	std::vector<const SdlTexture*> sUp;
	std::vector<const SdlTexture*> sShooting;
	std::vector<const SdlTexture*> sDying;
	const double animationSpeed;
	int id_weapon;
	bool isRunning;
	bool isShooting;
	bool isAlive;

	bool animarDisparo;
	bool animarMuerte;
	double image_index;

	public:
		Enemy(double xInicial, double yInicial, SDL_Rect clip, double dirInicial,
			std::vector<const SdlTexture*> sDown, std::vector<const SdlTexture*> sDownLeft,
			std::vector<const SdlTexture*> sLeft, std::vector<const SdlTexture*> sUpLeft,
			std::vector<const SdlTexture*> sUp, std::vector<const SdlTexture*> sShooting,
			std::vector<const SdlTexture*> sDying,
			ClientSettings& settings);
		~Enemy();
		void setRelativeDirection(double enemyDirection, double playerDirection);
		void setWeapon(int id_newWeapon);
		void setIsRunning(bool isRunning);
		void setIsShooting(bool isShooting);
		void setIsAlive(bool isAlive);
		void actualizar() override;
};

#endif  // ENEMY_H
