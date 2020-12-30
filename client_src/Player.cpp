#include "Player.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"

Player::Player(const SdlTexture& texture, float xInicial, float yInicial,
	 float dirInicial, float vidaInicial):
		texture(texture),
	  x(xInicial),
	  y(yInicial),
	  direction(dirInicial),
		health(vidaInicial) {
			SDL_Rect clip = {0, 0, 64, 64};
			this->idArmaActual = 0;
			this->weaponClip = clip;
			this->frameActual = 0;
			this->cantFrames = 5;
			this->drawScale = 6;
			this->animarArma = false;
			this->cuchillo = new PlayerWeapon(999, true);
			this->pistola = new PlayerWeapon(10, true);
			this->ametralladora = new PlayerWeapon(0, false);
			this->canionDeCadena =  new PlayerWeapon(0, false);
			this->lanzacohetes =  new PlayerWeapon(0, false);
}

Player::~Player() {
	delete this->cuchillo;
	delete this->pistola;
	delete this->ametralladora;
	delete this->canionDeCadena;
	delete this->lanzacohetes;
}

float Player::getX() const {
	return x;
}

float Player::getY() const {
	return y;
}

float Player::getDirection() const {
	return direction;
}

int Player::getHealth() const {
	return int(health);
}

void Player::setPosicion(float x, float y) {
	this->x = x;
	this->y = y;
}

void Player::setDirection(float direction) {
	this->direction = direction;
}

void Player::setHealth(float health) {
	this->health = health;
}

void Player::setArmaActual(int idArma) {
	if ((idArma>= 0) && (idArma <= 3)) {
		idArmaActual = idArma;
		this->weaponClip.y = (64+1)*idArma;
	}
}

void Player::renderizar(SdlRenderer& renderer, ClientSettings& settings) {
	SDL_Rect auxClip = weaponClip;
	auxClip.x += int(frameActual)*65;
	renderer.renderCopyCentered(texture, &auxClip, settings.screenWidth/2, settings.screenHeight-(weaponClip.h/2)*drawScale, drawScale, drawScale);
	if (animarArma) {
		frameActual += (float(2) * cantFrames / settings.fps);
		if (frameActual >= cantFrames) {
			frameActual = 0;
			animarArma = false;
		}
	}
}
