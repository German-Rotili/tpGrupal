#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "../common_src/SDLWrappers/SdlTexture.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "ResourcesLoader.h"
#include "../common_src/SDLWrappers/SdlSound.h"

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
	std::vector<const SdlSound*> sndWeapons;
	const SdlSound& sndDying;
	const double animationSpeed;
	int id_weapon;
	bool isRunning;
	bool isAlive;

	bool animarDisparo;
	bool animarMuerte;
	double image_index;

	public:
		Enemy(double xInicial, double yInicial, SDL_Rect clip, double dirInicial,
			Player& player, ResourcesLoader& src, ClientSettings& settings);
		~Enemy();
		void setRelativeDirection(double enemyDirection, double playerDirection);
		void setWeapon(int id_newWeapon);
		void setIsRunning(bool isRunning);
		void setShootingAction();
		void setIsAlive(bool isAlive);
		void update() override;
};

#endif  // ENEMY_H
