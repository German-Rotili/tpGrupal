#include <algorithm>
#include <cmath>
#include "Enemy.h"
#include "ClientSettings.h"


Enemy::Enemy(double xInicial, double yInicial, SDL_Rect clip, double dirInicial,
	Player& player, ResourcesLoader& src, ClientSettings& settings):
		ZRenderable(xInicial, yInicial, clip, player, settings),
		relativeDirection(dirInicial),
		sDown({&src.tx_guardDogDown, &src.tx_guardDown, &src.tx_ssDown, &src.tx_officerDown, &src.tx_mutantDown}),
		sDownLeft({&src.tx_guardDogDownLeft, &src.tx_guardDownLeft, &src.tx_ssDownLeft, &src.tx_officerDownLeft, &src.tx_mutantDownLeft}),
		sLeft({&src.tx_guardDogLeft, &src.tx_guardLeft, &src.tx_ssLeft, &src.tx_officerLeft, &src.tx_mutantLeft}),
		sUpLeft({&src.tx_guardDogUpLeft, &src.tx_guardUpLeft, &src.tx_ssUpLeft, &src.tx_officerUpLeft, &src.tx_mutantUpLeft}),
		sUp({&src.tx_guardDogUp, &src.tx_guardUp, &src.tx_ssUp, &src.tx_officerUp, &src.tx_mutantUp}),
		sShooting({&src.tx_guardDogShooting, &src.tx_guardShooting, &src.tx_ssShooting, &src.tx_officerShooting, &src.tx_mutantShooting}),
		sDying({&src.tx_guardDogDying, &src.tx_guardDying, &src.tx_ssDying, &src.tx_officerDying, &src.tx_mutantDying}),
		sndWeapons({&src.snd_cuchillo, &src.snd_pistola1, &src.snd_ametralladora1, &src.snd_canionDeCadena, &src.snd_lanzacohetes}),
		sndDying(src.snd_dying),
		animationSpeed(double(8) / settings.fps) {
			id_weapon = 4;
			isRunning = false;
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
void Enemy::setShootingAction() {
	animarDisparo = true;
	image_index = 1;
	// Sonido de disparo
	this->setDifAnglePlayer();
	int soundAngle = this->getDifAnglePlayer();
	if (soundAngle < 0) {
		soundAngle += 360;
	}
	sndWeapons[id_weapon]->playInPosition(-1, 0, soundAngle, std::min(int(player.getDistanceToPoint(x, y) * 22), 255));
	//
}
void Enemy::setIsAlive(bool isAlive) {
	if (this->isAlive && !isAlive) {
		animarMuerte = true;
		image_index = 0;
		// Sonido de muerte
		this->setDifAnglePlayer();
		int soundAngle = this->getDifAnglePlayer();
		if (soundAngle < 0) {
			soundAngle += 360;
		}
		sndDying.playInPosition(-1, 0, soundAngle, std::min(int(player.getDistanceToPoint(x, y) * 22), 255));

	} else if (!this->isAlive && isAlive) {
		animarMuerte = false;
	}
	this->isAlive = isAlive;
}

void Enemy::update() {
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
