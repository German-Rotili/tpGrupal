#include <cmath>
#include "Object.h"
#include "ClientSettings.h"

Object::Object(const SdlTexture& texture, SDL_Rect clip,
	 double xInicial, double yInicial):
		texture(texture),
		clip(clip),
		x(xInicial),
		y(yInicial) {
			this->difAngle = 0;
			this->distToPlayer = 100;
		}

Object::~Object() {}

void Object::setDifAngle(double actorX, double actorY, double actorAngle) {
	double angle = (atan2(actorY - y, actorX - x) - M_PI) * 180 / M_PI;
	this->difAngle = (angle - actorAngle);
	if (this->difAngle > 180) {
		this->difAngle -= 360;
	}
	if (this->difAngle <-180) {
		this->difAngle += 360;
	}
}

void Object::setPosicion(double x, double y) {
	this->x = x;
	this->y = y;
}

double Object::getX() {
	return this->x;
}

double Object::getY() {
	return this->y;
}

double Object::getDifAngle() {
	return this->difAngle;
}

double Object::getDistToPlayer() {
	return this->distToPlayer;
}

bool Object::esVisibleDesde(double actorX, double actorY, double actorAngle, ClientSettings& settings) {
	setDifAngle(actorX, actorY, actorAngle);
	double absDifAngle = abs(getDifAngle());
	if (absDifAngle <= (settings.fov/1)) {
		distToPlayer = settings.distance(actorX, actorY, x, y);
		return true;
	}
	return false;
}

void Object::renderizar(SdlRenderer& renderer, double zBuffer[],
	 ClientSettings& settings) {
	double proy = distToPlayer * cos(difAngle*M_PI/180);
	double scale = (1/proy) * settings.screenHeight / clip.w;
	double x0 = settings.screenWidth/2 + tan(difAngle*M_PI/180) * settings.screenWidth - (clip.w/2)*scale;
	double y0 = settings.screenHeight/2 - (clip.h/2)*scale;
	SDL_Rect auxClip = this->clip;
	auxClip.w = 1;
	for (int i = 0; i < clip.w; i++) {
		for (int j = 0; j <= round(scale); j++) {
			if ((x0 >= 0) && (x0+j < settings.screenWidth) && (zBuffer[int(x0)+j] > distToPlayer))
				renderer.renderCopy(this->texture, &auxClip, x0+j, y0, 1, scale);
		}
		x0 += scale;
		auxClip.x+=1;
	}
}
