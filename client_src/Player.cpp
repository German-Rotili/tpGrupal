#include "Player.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"

Player::Player(const SdlTexture& texture, float xInicial, float yInicial,
	float dirInicial, float healthInicial, int scoreInicial, int livesInicial):
		texture(texture),
	  x(xInicial),
	  y(yInicial),
	  direction(dirInicial),
		health(healthInicial),
		score(scoreInicial),
		lives(livesInicial) {
			SDL_Rect clip_armaInicial = {0, 65, 64, 64};
			this->weaponClip = clip_armaInicial;
			this->frameActual = 0;
			this->cantFrames = 5;
			this->drawScale = 6;
			this->animarArma = false;
			this->cuchillo = new PlayerWeapon(true, 999);
			this->pistola = new PlayerWeapon(true, 10);
			this->ametralladora = new PlayerWeapon(true, 0);
			this->canionDeCadena =  new PlayerWeapon(true, 0);
			this->lanzacohetes =  new PlayerWeapon(true, 0);
			this->armaActual = this->pistola;
			this->idArmaActual = 1;
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

int Player::getCantBalasArmaActual() const {
	return armaActual->getCantBalas();
}

int Player::getScore() const {
	return score;
}

int Player::getLives() const {
	return lives;
}

int Player::getIdArmaActual() const {
	return idArmaActual;
}

std::vector<bool> Player::getArmasDisponibles() const {
	std::vector<bool> resultado = {
		cuchillo->estaDisponible(),
		pistola->estaDisponible(),
		ametralladora->estaDisponible(),
		canionDeCadena->estaDisponible(),
		lanzacohetes->estaDisponible()
	};
	return resultado;
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

void Player::setScore(int score) {
	this->score = score;
}

void Player::setArmaActual(int idArma) {
	if (idArma == 0) {
		armaActual = cuchillo;
	} else if (idArma == 1) {
		armaActual = pistola;
	} else if (idArma == 2) {
		armaActual = ametralladora;
	} else if (idArma == 3) {
		armaActual = canionDeCadena;
	} else if (idArma == 4) {
		armaActual = lanzacohetes;
	} else {
		return;
	}
	this->weaponClip.y = (64+1)*idArma;
	idArmaActual = idArma;
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
