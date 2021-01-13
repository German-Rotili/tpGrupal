#include <cmath>
#include "Enemy.h"
#include "ClientSettings.h"

Enemy::Enemy(double xInicial, double yInicial, SDL_Rect clip, double dirInicial,
	std::vector<const SdlTexture*> sDown, std::vector<const SdlTexture*> sDownLeft,
	std::vector<const SdlTexture*> sLeft, std::vector<const SdlTexture*> sUpLeft,
	std::vector<const SdlTexture*> sUp, std::vector<const SdlTexture*> sShooting,
	 std::vector<const SdlTexture*> sDying,
	ClientSettings& settings):
		ZRenderable(xInicial, yInicial, clip),
		relativeDirection(dirInicial),
		sDown(sDown),
		sDownLeft(sDownLeft),
		sLeft(sLeft),
		sUpLeft(sUpLeft),
		sUp(sUp),
		sShooting(sShooting),
		sDying(sDying),
		animationSpeed(double(8) / settings.fps) {
			id_weapon = 4;
			isRunning = false;
			isShooting = false;
			isAlive = true;
			animarDisparo = false;
			animarMuerte = false;
			image_index = 0;
			currentTexture = sDown[id_weapon];
		}

Enemy::~Enemy() {}

void Enemy::setRelativeDirection(double enemyDirection, double playerDirection) {
	relativeDirection = playerDirection - enemyDirection - 90 ;
	if (relativeDirection <= -360) {
		relativeDirection += 360;
	}
	else if (relativeDirection > 0) {
		relativeDirection -= 360;
	}
}

void Enemy::setWeapon(int id_newWeapon) {
	this->id_weapon = id_newWeapon;
}

void Enemy::setIsRunning(bool isRunning) {
	this->isRunning = isRunning;
}
void Enemy::setIsShooting(bool isShooting) {
	if ((!this->isShooting) && (isShooting)) {
		animarDisparo = true;
		image_index = 0;
	}
	this->isShooting = isShooting;
}
void Enemy::setIsAlive(bool isAlive) {
	if (this->isAlive && !isAlive) {
		animarMuerte = true;
		image_index = 0;
	} else if (!this->isAlive && isAlive) {
		animarMuerte = false;
	}
	this->isAlive = isAlive;
}

void Enemy::actualizar() {
	if (animarMuerte) {
		currentTexture = sDying[id_weapon];
		clip.x = int(image_index) * 64;
		if (image_index < 4) {
			image_index += animationSpeed;
		}
	} else {
		if (animarDisparo) {
			currentTexture = sShooting[id_weapon];
			clip.x = int(image_index) * 64;
			image_index += animationSpeed;
			if (image_index >= 3) {
				animarDisparo = false;
			}
		} else {
			if (isRunning) {
				clip.x = int(image_index + 1) * 64;
				image_index += animationSpeed;
				if (image_index >= 4) {
					image_index -= 4;
				}
			} else {
				clip.x = 0;
			}
			flipType = SDL_FLIP_NONE;
			if ((relativeDirection <= -0 && relativeDirection >= -22.5) ||
			(relativeDirection <= -337.5 && relativeDirection > -360)) {
				currentTexture = sLeft[id_weapon];
			} else if (relativeDirection < -22.5 && relativeDirection >=-67.5) {
				currentTexture = sUpLeft[id_weapon];
			} else if (relativeDirection < -67.5 && relativeDirection >= -112.5) {
				currentTexture = sUp[id_weapon];
			} else if (relativeDirection < -112.5 && relativeDirection >= -157.5) {
				currentTexture = sUpLeft[id_weapon];
				flipType = SDL_FLIP_HORIZONTAL;  // MirrorX
			} else if (relativeDirection < -157.5 && relativeDirection >= -202.5) {
				currentTexture = sLeft[id_weapon];
				flipType = SDL_FLIP_HORIZONTAL;  // MirrorX
			} else if (relativeDirection < -202.5 && relativeDirection >= -247.5) {
				currentTexture = sDownLeft[id_weapon];
				flipType = SDL_FLIP_HORIZONTAL;  // MirrorX
			} else if (relativeDirection < -247.5 && relativeDirection >= -292.5) {
				currentTexture = sDown[id_weapon];
			} else if (relativeDirection < -292.5 && relativeDirection >= -337.5) {
				currentTexture = sDownLeft[id_weapon];
			}
		}
	}
}
