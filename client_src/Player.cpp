#include "Player.h"
#include "../common_src/SDLWrappers/SdlTexture.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"

Player::Player(SdlRenderer& renderer, ResourcesLoader& src, const ClientSettings& settings,
	double xInicial, double yInicial, double dirInicial, double healthInicial,
	int scoreInicial, int livesInicial):
		renderer(renderer),
		texture(renderer, "../resources/textures/player.png", 152, 0, 136),
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
		cuchillo(true, src.snd_cuchillo, src.snd_cuchillo),
		pistola(true, src.snd_pistola1, src.snd_pistola2),
		ametralladora(true, src.snd_ametralladora1, src.snd_ametralladora2),
		canionDeCadena(true, src.snd_canionDeCadena, src.snd_canionDeCadena),
		lanzacohetes(true, src.snd_lanzacohetes, src.snd_lanzacohetes),
		sndDying(src.snd_dying),
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

double Player::getDistanceToPoint(double x, double y) const {
	return sqrt(pow(x-this->x, 2) + pow(y-this->y, 2));
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
	if ((health <= 0) & (this->health > 0)) {
		sndDying.play(-1, 0);
	}
	this->health = health;
}

void Player::setLives(int lives) {
	this->lives = lives;
}

void Player::setScore(int score) {
	this->score = score;
}
void Player::setShootingAction() {
	this->frameActual = 2;
	this->animarArma = true;
	this->armaActual->reproducirSonido();
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

void Player::render(ClientSettings& settings) {
	SDL_Rect auxClip = weaponClip;
	auxClip.x += int(frameActual)*65;
	if (animarArma) {
		frameActual += animationSpeed;
		if (frameActual >= cantFrames) {
			frameActual = 0;
			animarArma = false;
		}
	}
	if (this->health > 0) {
		renderer.renderCopyCentered(texture, &auxClip, DRAW_WEAPON_X, DRAW_WEAPON_Y, DRAW_SCALE, DRAW_SCALE);
	}
}
