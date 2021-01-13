#include <cmath>
#include "ZRenderable.h"
#include "ClientSettings.h"

ZRenderable::ZRenderable(double xInicial, double yInicial, SDL_Rect clip):
		x(xInicial),
		y(yInicial),
		clip(clip),
		flipType(SDL_FLIP_NONE) {
			this->difAngle = 0;
			this->distToPlayer = 100;
		}

ZRenderable::~ZRenderable() {}

void ZRenderable::setDifAngle(double actorX, double actorY, double actorAngle) {
	double angle = (atan2(actorY - y, actorX - x) - M_PI) * 180 / M_PI;
	this->difAngle = (angle - actorAngle);
	if (this->difAngle > 180) {
		this->difAngle -= 360;
	}
	if (this->difAngle <-180) {
		this->difAngle += 360;
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

double ZRenderable::getDifAngle() {
	return this->difAngle;
}

double ZRenderable::getDistToPlayer() {
	return this->distToPlayer;
}

bool ZRenderable::esVisibleDesde(double actorX, double actorY, double actorAngle, ClientSettings& settings) {
	setDifAngle(actorX, actorY, actorAngle);
	double absDifAngle = abs(getDifAngle());
	if (absDifAngle <= (settings.fov/1)) {
		return true;
	}
	return false;
}

void ZRenderable::updateDistToPlayer(double actorX, double actorY, ClientSettings& settings) {
	distToPlayer = settings.distance(actorX, actorY, x, y);
}

void ZRenderable::renderizar(SdlRenderer& renderer, double zBuffer[],
	 ClientSettings& settings) {
	double proy = distToPlayer * cos(difAngle*M_PI/180);
	double scale = (1/proy) * settings.screenHeight / clip.w;
	double x0 = settings.screenWidth/2 + tan(difAngle*M_PI/180) * settings.screenWidth - (clip.w/2)*scale;
	double y0 = settings.screenHeight/2 - (clip.h/2)*scale;
	SDL_Rect auxClip = this->clip;
	auxClip.w = 1;
	int sumar = 1;
	if (flipType == SDL_FLIP_HORIZONTAL) {
		sumar = -1;
		auxClip.x += 63;
	}
	for (int i = 0; i < clip.w; i++) {
		for (int j = 0; j <= round(scale); j++) {
			if ((x0 >= 0) && (x0+j < settings.screenWidth) && (zBuffer[int(x0)+j] > distToPlayer))
				renderer.renderCopy(*currentTexture, &auxClip, x0+j, y0, 1, scale);
		}
		x0 += scale;
		auxClip.x += sumar;
	}
}
