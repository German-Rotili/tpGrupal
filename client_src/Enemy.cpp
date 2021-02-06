#include <algorithm>
#include <cmath>
#include "Enemy.h"
#include "ClientSettings.h"


Enemy::Enemy(double xInicial, double yInicial, SDL_Rect clip, double dirInicial,
	Player& player, ResourcesLoader& rc, ClientSettings& settings):
		ZRenderable(xInicial, yInicial, clip, player, settings),
		relativeDirection(dirInicial),
		sDown({&rc.tx_guardDogDown, &rc.tx_guardDown, &rc.tx_ssDown, &rc.tx_officerDown, &rc.tx_mutantDown}),
		sDownLeft({&rc.tx_guardDogDownLeft, &rc.tx_guardDownLeft, &rc.tx_ssDownLeft, &rc.tx_officerDownLeft, &rc.tx_mutantDownLeft}),
		sLeft({&rc.tx_guardDogLeft, &rc.tx_guardLeft, &rc.tx_ssLeft, &rc.tx_officerLeft, &rc.tx_mutantLeft}),
		sUpLeft({&rc.tx_guardDogUpLeft, &rc.tx_guardUpLeft, &rc.tx_ssUpLeft, &rc.tx_officerUpLeft, &rc.tx_mutantUpLeft}),
		sUp({&rc.tx_guardDogUp, &rc.tx_guardUp, &rc.tx_ssUp, &rc.tx_officerUp, &rc.tx_mutantUp}),
		sShooting({&rc.tx_guardDogShooting, &rc.tx_guardShooting, &rc.tx_ssShooting, &rc.tx_officerShooting, &rc.tx_mutantShooting}),
		sDying({&rc.tx_guardDogDying, &rc.tx_guardDying, &rc.tx_ssDying, &rc.tx_officerDying, &rc.tx_mutantDying}),
		sndWeapons({&rc.snd_cuchillo, &rc.snd_pistola1, &rc.snd_ametralladora1, &rc.snd_canionDeCadena, &rc.snd_lanzacohetes}),
		sndDying(rc.snd_dying),
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
		image_index = 1;

		// Sonido de disparo
		this->setDifAnglePlayer();
		int angulosonido = this->getDifAnglePlayer();
		if (angulosonido < 0) {
			angulosonido += 360;
		}
		sndWeapons[id_weapon]->playInPosition(-1, 0, angulosonido, std::min(int(player.getDistanceToPoint(x, y) * 22), 255));
	}
	this->isShooting = isShooting;
}
void Enemy::setIsAlive(bool isAlive) {
	if (this->isAlive && !isAlive) {
		animarMuerte = true;
		image_index = 0;
		// Sonido de muerte
		this->setDifAnglePlayer();
		int angulosonido = this->getDifAnglePlayer();
		if (angulosonido < 0) {
			angulosonido += 360;
		}
		sndDying.playInPosition(-1, 0, angulosonido, std::min(int(player.getDistanceToPoint(x, y) * 22), 255));

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
				if (image_index >= 3.999) {
					image_index = 0;
				}
				clip.x = int(image_index + 1) * 64;
				image_index += animationSpeed;
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
