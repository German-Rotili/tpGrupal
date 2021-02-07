#include <cmath>
#include "ZRenderable.h"
#include "ClientSettings.h"

ZRenderable::ZRenderable(double xInicial, double yInicial, SDL_Rect clip, Player& player, ClientSettings& settings):
		x(xInicial),
		y(yInicial),
		clip(clip),
		player(player),
		flipType(SDL_FLIP_NONE),
		HALF_SCREENW(settings.screenWidth/2),
		HALF_SCREENH(settings.screenHeight/2),
		HALF_CLIPW(clip.w/2),
		HALF_CLIPH(clip.h/2),
		SCREENHEIGHT_CLIPW(settings.screenHeight/clip.w) {
			this->difAnglePlayer = 0;
			this->distToPlayer = 100;
		}

ZRenderable::~ZRenderable() {}

void ZRenderable::setDifAnglePlayer() {
	double angle = (atan2(player.getY() - y, player.getX() - x) - M_PI) * 180 / M_PI;
	this->difAnglePlayer = (angle - player.getDirection());
	if (this->difAnglePlayer > 180) {
		this->difAnglePlayer -= 360;
	}
	if (this->difAnglePlayer <-180) {
		this->difAnglePlayer += 360;
	}
}

void ZRenderable::setPosicion(double x, double y) {
	this->x = x;
	this->y = y;
}

double ZRenderable::getX() {
	return this->x;
}

double ZRenderable::getY() {
	return this->y;
}

double ZRenderable::getDifAnglePlayer() {
	return this->difAnglePlayer;
}

double ZRenderable::getDistToPlayer() {
	return this->distToPlayer;
}

bool ZRenderable::esVisiblePorPlayer(ClientSettings& settings) {
	if ((player.getX() == x) && (player.getY() == y))
		return false;
	setDifAnglePlayer();
	double absDifAngle = abs(getDifAnglePlayer());
	if (absDifAngle <= (settings.fov)) {
		return true;
	}
	return false;
}

void ZRenderable::updateDistToPlayer() {
	distToPlayer = player.getDistanceToPoint(x, y);
}

void ZRenderable::renderizar(SdlRenderer& renderer, double zBuffer[],
	 ClientSettings& settings) {
	double proy = distToPlayer * cos(difAnglePlayer*M_PI_180);
	double scale = (1/proy) * SCREENHEIGHT_CLIPW;
	double x0 = HALF_SCREENW + tan(difAnglePlayer*M_PI_180) * settings.screenWidth - HALF_CLIPW * scale;
	double y0 = HALF_SCREENH - (HALF_CLIPH)*scale;
	SDL_Rect auxClip = this->clip;
	auxClip.w = 1;
	int sumar = 1;
	if (flipType == SDL_FLIP_HORIZONTAL) {
		sumar = -1;
		auxClip.x += 63;
	}
	for (int i = 0; i < clip.w; i++) {
		if (x0 >= 0) {
			int limite = x0 + scale;
			for (int j = 0; (x0 + j) < limite; j++) {
				if ((x0+j < settings.screenWidth) && (zBuffer[int(x0)+j] > distToPlayer))
					renderer.renderCopy(*currentTexture, &auxClip, x0+j, y0, 1, scale);
			}
		}
		x0 += scale;
		auxClip.x += sumar;
	}
}
