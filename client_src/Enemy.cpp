#include <cmath>
#include "Enemy.h"
#include "ClientSettings.h"

Enemy::Enemy(double xInicial, double yInicial, SDL_Rect clip, double dirInicial,
	const SdlTexture& sDown, const SdlTexture& sDownLeft,
	const SdlTexture& sLeft, const SdlTexture& sUpLeft,
	const SdlTexture& sUp, const SdlTexture& sShooting, const SdlTexture& sDying,
	ClientSettings& settings):
		ZRenderable(xInicial, yInicial, clip),
		direction(dirInicial),
		sDown(sDown),
		sDownLeft(sDownLeft),
		sLeft(sLeft),
		sUpLeft(sUpLeft),
		sUp(sUp),
		sShooting(sShooting),
		sDying(sDying),
		animationSpeed(double(4) / settings.fps) {
			image_index = 0;
			playerDirection = 0;
			currentTexture = &sDown;
		}

Enemy::~Enemy() {}

void Enemy::setDirections(double newDirection, double newPlayerDirection) {
	direction = newDirection;
	playerDirection = newPlayerDirection;
}

void Enemy::actualizar() {
	// update animation
	image_index += animationSpeed;
	if (image_index >= 5) {
		image_index -= 5;
	}
	clip.x = int(image_index) * 64;
	// update Texture
	double auxDirection = direction - playerDirection;
	if (auxDirection < 0) {
		auxDirection += 360;
	}
	flipType = SDL_FLIP_NONE;
	if ((auxDirection >= 0 && auxDirection <= 22.5) ||
	(auxDirection >= 337.5 && auxDirection < 360)) {
		currentTexture = &sLeft;
	} else if (auxDirection > 22.5 && auxDirection <=67.5) {
		currentTexture = &sUpLeft;
	} else if (auxDirection > 67.5 && auxDirection <= 112.5) {
		currentTexture = &sUp;
	} else if (auxDirection > 112.5 && auxDirection <= 157.5) {
		currentTexture = &sUpLeft;
		flipType = SDL_FLIP_HORIZONTAL;  // MirrorX
	} else if (auxDirection > 157.5 && auxDirection <= 202.5) {
		currentTexture = &sLeft;
		flipType = SDL_FLIP_HORIZONTAL;  // MirrorX
	} else if (auxDirection > 202.5 && auxDirection <= 247.5) {
		currentTexture = &sDownLeft;
		flipType = SDL_FLIP_HORIZONTAL;  // MirrorX
	} else if (auxDirection > 247.5 && auxDirection <= 292.5) {
		currentTexture = &sDown;
	} else if (auxDirection > 292.5 && auxDirection <= 337.5) {
		currentTexture = &sDownLeft;
	}
}
