#include "Player.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"

Player::Player(SdlRenderer& renderer, ResourcesLoader& rc, const ClientSettings& settings,
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
		isShooting(false),
		weaponClip({0, 65, 64, 64}),
		frameActual(0),
		cantFrames(5),
		DRAW_WEAPON_X(settings.screenWidth/2),
		DRAW_SCALE(double(settings.screenWidth) * 0.00586),
		DRAW_WEAPON_Y(settings.screenHeight-(weaponClip.h/2)*DRAW_SCALE),
		animationSpeed(double(2) * cantFrames / settings.fps),
		cuchillo(true, rc.snd_cuchillo, rc.snd_cuchillo),
		pistola(true, rc.snd_pistola1, rc.snd_pistola2),
		ametralladora(true, rc.snd_ametralladora1, rc.snd_ametralladora2),
		canionDeCadena(true, rc.snd_canionDeCadena, rc.snd_canionDeCadena),
		lanzacohetes(true, rc.snd_lanzacohetes, rc.snd_lanzacohetes),
		cantBalas(8) {
			armaActual = &pistola;
			this->animarArma = false;
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

int Player::getCantBalas() const {
	return cantBalas;
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

void Player::setLives(int lives) {
	this->lives = lives;
}

void Player::setScore(int score) {
	this->score = score;
}
void Player::setIsShooting(bool isShooting) {
	if (!this->isShooting && (isShooting)) {
		this->frameActual = 2;
		this->animarArma = true;
		this->armaActual->reproducirSonido();
	}
	this->isShooting = isShooting;
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
	}
	this->weaponClip.y = (64+1)*idArma;
	idArmaActual = idArma;
}

void Player::setCantBalas(int cantBalas) {
	this->cantBalas = cantBalas;
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
