#include "Player.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"

Player::Player(SdlRenderer& renderer, const ClientSettings& settings,
	double xInicial, double yInicial, double dirInicial, double healthInicial,
	int scoreInicial, int livesInicial):
		renderer(renderer),
		texture(renderer, "textures/player.png", 152, 0, 136),
	  x(xInicial),
	  y(yInicial),
	  direction(dirInicial),
		health(healthInicial),
		score(scoreInicial),
		lives(livesInicial),
		weaponClip({0, 65, 64, 64}),
		frameActual(0),
		cantFrames(5),
		DRAW_WEAPON_X(settings.screenWidth/2),
		DRAW_SCALE(double(settings.screenWidth) * 0.00586),
		DRAW_WEAPON_Y(settings.screenHeight-(weaponClip.h/2)*DRAW_SCALE),
		animationSpeed(double(2) * cantFrames / settings.fps),
		cuchillo(true, 999),
		pistola(true, 8),
		ametralladora(true, 0),
		canionDeCadena(true, 0),
		lanzacohetes(true, 0) {
			this->animarArma = false;
			this->armaActual = &pistola;
			this->idArmaActual = 1;
}

Player::~Player() {
}

double Player::getX() const {
	return x;
}

double Player::getY() const {
	return y;
}

double Player::getDirection() const {
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
		cuchillo.estaDisponible(),
		pistola.estaDisponible(),
		ametralladora.estaDisponible(),
		canionDeCadena.estaDisponible(),
		lanzacohetes.estaDisponible()
	};
	return resultado;
}

void Player::setPosicion(double x, double y) {
	this->x = x;
	this->y = y;
}

void Player::setDirection(double direction) {
	this->direction = direction;
}

void Player::setHealth(double health) {
	this->health = health;
}

void Player::setScore(int score) {
	this->score = score;
}

void Player::setArmaActual(int idArma) {
	if (idArma == 0) {
		armaActual = &cuchillo;
	} else if (idArma == 1) {
		armaActual = &pistola;
	} else if (idArma == 2) {
		armaActual = &ametralladora;
	} else if (idArma == 3) {
		armaActual = &canionDeCadena;
	} else if (idArma == 4) {
		armaActual = &lanzacohetes;
	} else {
		return;
	}
	this->weaponClip.y = (64+1)*idArma;
	idArmaActual = idArma;
}

void Player::renderizar(ClientSettings& settings) {
	SDL_Rect auxClip = weaponClip;
	auxClip.x += int(frameActual)*65;
	if (animarArma) {
		frameActual += animationSpeed;
		if (frameActual >= cantFrames) {
			frameActual = 0;
			animarArma = false;
		}
	}
	renderer.renderCopyCentered(texture, &auxClip, DRAW_WEAPON_X, DRAW_WEAPON_Y, DRAW_SCALE, DRAW_SCALE);
}
