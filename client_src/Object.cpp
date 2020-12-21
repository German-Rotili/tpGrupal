#include "Object.h"
#include "ClientSettings.h"

Object::Object(const SdlTexture& texture, SDL_Rect clip,
	 float xInicial, float yInicial):
		texture(texture),
		clip(clip),
		x(xInicial),
		y(yInicial) {
			this->difAngle = 0;
			this->distToPlayer = 100;
		}

Object::~Object() {}

void Object::actualizarPosicion(float x, float y) {
	this->x = x;
	this->y = y;
}

void Object::actualizarDistToPlayer(float actorX, float actorY, ClientSettings& settings) {
	distToPlayer = settings.distance(actorX, actorY, x, y);
}

float Object::getX() {
	return this->x;
}

float Object::getY() {
	return this->y;
}

float Object::getDifAngle() {
	return this->difAngle;
}

float Object::getDistToPlayer() {
	return this->distToPlayer;
}

void Object::actualizarDifAngle(float actorX, float actorY, float actorAngle, ClientSettings& settings) {
	float angle = (atan2(actorY - y, actorX - x) - settings.pi) * 180 / settings.pi;
	this->difAngle = (angle - actorAngle);
	if (this->difAngle > 180) {
		this->difAngle -= 360;
	}
	if (this->difAngle <-180) {
		this->difAngle += 360;
	}
}

void Object::renderizar(SdlRenderer& renderer,
	double zBuffer[], ClientSettings& settings) {
	float proy = distToPlayer * cos(difAngle*settings.pi/180);
	float scale = (1/proy) * settings.screenHeight / clip.w;
	float x0 = settings.screenWidth/2 + tan(difAngle*settings.pi/180) * settings.screenWidth - (clip.w/2)*scale;
	float y0 = settings.screenHeight/2 - (clip.h/2)*scale;
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
