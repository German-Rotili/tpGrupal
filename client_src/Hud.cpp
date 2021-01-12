#include "Hud.h"
#include <string>
#include <cmath>
#include "Player.h"
#include "ClientSettings.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlFont.h"

Hud::Hud(class SdlRenderer& renderer, const class Player& player, const ClientSettings& settings):
	FONT_SIZE(round(double(settings.screenWidth) * 0.05)),
	COLUMNA1(settings.screenWidth * 1/16),
	COLUMNA2(settings.screenWidth * 4/24),
	COLUMNA3(settings.screenWidth * 2/8),
	COLUMNA4(settings.screenWidth * 6/8),
	COLUMNA5(settings.screenWidth * 15/16),
	FILA1(settings.screenHeight - FONT_SIZE * 2.5),
	FILA2(settings.screenHeight - FONT_SIZE),
	renderer(renderer),
	font("fonts/hudFont.ttf", FONT_SIZE),
	player(player),
	faceClip({25, 0, 24, 32}),
	faceScale(double(settings.screenWidth) * 0.001953),
	playerFaces(renderer, "textures/playerFaces.png"),
	weapon1(renderer, font, "1", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon2(renderer, font, "2", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon3(renderer, font, "3", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon4(renderer, font, "4", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon5(renderer, font, "5", c_yellow.r, c_yellow.g, c_yellow.b) {
		playerFaceAnimation = 0;
		playerWaitAnimation = rand() % 200;
		rectangleScreen_alpha = 0;
		displayHealth = -1;
		displayAmmo = -1;
		displayScore = -1;
		displayLives = -1;
		ammoTexture = NULL;
		healthTexture = NULL;
		scoreTexture = NULL;
		livesTexture = NULL;
		actualizar();
		rectangleScreen_alpha = 0;
}

Hud::~Hud() {
	delete ammoTexture;
	delete healthTexture;
	delete scoreTexture;
	delete livesTexture;
}

void Hud::actualizarFaceBlood() {
	if (displayHealth <= 0) {
		faceClip.y = 33*6;
	}
	else if (displayHealth >= 100) {
		faceClip.y = 0;
	}
	else {
		faceClip.y = 33 * int((100-displayHealth)*7/100);
	}
}
void Hud::actualizarFaceAnimation() {
	if (playerWaitAnimation == 0) {
		playerFaceAnimation += 0.1;
		if (playerFaceAnimation > (2*M_PI)) {
			playerFaceAnimation = 0;
			playerWaitAnimation = rand() % 200;
		}
		faceClip.x = 25 + 25*round((sin(playerFaceAnimation)));
	} else {
		playerWaitAnimation -= 1;
	}
}

void Hud::actualizarAmmo() {
	int auxAmmo = player.getCantBalasArmaActual();
	if (auxAmmo != displayAmmo) {
		//if (auxAmmo > displayAmmo) {
		//	c_rectangleScreen = c_yellow;
		//	rectangleScreen_alpha = 240;
		//} Problema: Si cambio de arma y ese arma tiene mas balas se toma como que agarre mas balas
		displayAmmo = auxAmmo;
		delete ammoTexture;
		ammoTexture = new SdlTexture(renderer, font,
			std::to_string(displayAmmo), c_yellow.r, c_yellow.g, c_yellow.b);
	}
}

void Hud::actualizarHealth() {
	int auxHealth = player.getHealth();
	if (auxHealth < displayHealth) {
		c_rectangleScreen = c_red;
	} else if (auxHealth > displayHealth) {
		c_rectangleScreen = c_green;
	} else {
		return;
	}
	rectangleScreen_alpha = 240;
	displayHealth = auxHealth;
	delete healthTexture;
	healthTexture = new SdlTexture(renderer, font,
		"+" + std::to_string(displayHealth), c_green.r, c_green.g, c_green.b);
	actualizarFaceBlood();
}

void Hud::actualizarScore() {
	int auxScore = player.getScore();
	if (auxScore != displayScore) {
		if (auxScore > displayScore) {
			c_rectangleScreen = c_yellow;
			rectangleScreen_alpha = 240;
		}
		displayScore = auxScore;
		delete scoreTexture;
		scoreTexture = new SdlTexture(renderer, font,
			"$ " +std::to_string(displayScore), c_yellow.r, c_yellow.g, c_yellow.b);
	}
}

void Hud::actualizarLives() {
	int auxLives = player.getLives();
	if (auxLives != displayLives) {
		displayLives = auxLives;
		delete livesTexture;
		livesTexture = new SdlTexture(renderer, font,
			std::to_string(displayLives), c_green.r, c_green.g, c_green.b);
	}
}

void Hud::actualizarWeapons() {
	displayWeapons = player.getArmasDisponibles();
}

void Hud::actualizar() {
	if (rectangleScreen_alpha > 0) {
		rectangleScreen_alpha -= 20;
	}
	actualizarHealth();
	actualizarAmmo();
	actualizarScore();
	actualizarLives();
	actualizarWeapons();
	actualizarFaceAnimation();
}

void Hud::renderizar(const ClientSettings & settings) {
	if (rectangleScreen_alpha > 0) {
		renderer.setRenderDrawColor(c_rectangleScreen.r, c_rectangleScreen.g,
			c_rectangleScreen.b, rectangleScreen_alpha);
		renderer.renderFillRect(0, 0, settings.screenWidth, settings.screenHeight);
	}
	int rectSize = double(weapon1.getWidth() * 1.8);
	renderer.setRenderDrawColor(c_yellow.r, c_yellow.g, c_yellow.b, 255);
	renderer.renderDrawRect(COLUMNA3 - rectSize/2 + player.getIdArmaActual() * rectSize, FILA2-weapon1.getHeight()/2, rectSize, weapon1.getHeight());
	if (displayWeapons[0]) {
		renderer.renderCopyCentered(weapon1, NULL, COLUMNA3, FILA2);
	}
	if (displayWeapons[1]) {
		renderer.renderCopyCentered(weapon2, NULL, COLUMNA3 + rectSize, FILA2);
	}
	if (displayWeapons[2]) {
		renderer.renderCopyCentered(weapon3, NULL, COLUMNA3 + rectSize * 2, FILA2);
	}
	if (displayWeapons[3]) {
		renderer.renderCopyCentered(weapon4, NULL, COLUMNA3 + rectSize * 3, FILA2);
	}
	if (displayWeapons[4]) {
		renderer.renderCopyCentered(weapon5, NULL, COLUMNA3 + rectSize * 4, FILA2);
	}

	renderer.renderCopyCentered(playerFaces, &faceClip, COLUMNA4, FILA2, faceScale, faceScale);
	renderer.renderCopyCentered(*healthTexture, NULL, COLUMNA1, FILA2);
	renderer.renderCopyCentered(*livesTexture, NULL, COLUMNA2, FILA2);
	renderer.renderCopyCentered(*ammoTexture, NULL, COLUMNA5, FILA2);
	renderer.renderCopyCentered(*scoreTexture, NULL, COLUMNA5, FILA1);
}
