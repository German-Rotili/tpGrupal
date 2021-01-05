#include "Hud.h"
#include <string>
#include <cmath>
#include "Player.h"
#include "ClientSettings.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlFont.h"

Hud::Hud(class SdlRenderer& renderer, class SdlFont& font, const class Player& player):
	renderer(renderer),
	font(font),
	player(player),
	playerFaces(renderer, "textures/playerFaces.png"),
	weapon1(renderer, font, "1", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon2(renderer, font, "2", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon3(renderer, font, "3", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon4(renderer, font, "4", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon5(renderer, font, "5", c_yellow.r, c_yellow.g, c_yellow.b) {
		SDL_Rect clipInicial = {25, 0, 24, 32};
		faceClip = clipInicial;
		playerFaceAnimation = 0;
		playerWaitAnimation = rand() % 300;
		rectangleScreen_alpha = 0;
		displayHealth = -1;
		displayAmmo = -1;
		displayScore = -1;
		displayLives = -1;
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
			playerWaitAnimation = rand() % 300;
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
	this->actualizar();
	if (rectangleScreen_alpha > 0) {
		renderer.setRenderDrawColor(c_rectangleScreen.r, c_rectangleScreen.g,
			c_rectangleScreen.b, rectangleScreen_alpha);
		renderer.renderFillRect(0, 0, settings.screenWidth, settings.screenHeight);
	}
	renderer.setRenderDrawColor(c_yellow.r, c_yellow.g, c_yellow.b, 255);
	renderer.renderDrawRect(200-15 + player.getIdArmaActual() * 30,settings.screenHeight-65, 30, 50);
	if (displayWeapons[0]) {
		renderer.renderCopyCentered(weapon1, NULL, 200, settings.screenHeight - 40);
	}
	if (displayWeapons[1]) {
		renderer.renderCopyCentered(weapon2, NULL, 230, settings.screenHeight - 40);
	}
	if (displayWeapons[2]) {
		renderer.renderCopyCentered(weapon3, NULL, 260, settings.screenHeight - 40);
	}
	if (displayWeapons[3]) {
		renderer.renderCopyCentered(weapon4, NULL, 290, settings.screenHeight - 40);
	}
	if (displayWeapons[4]) {
		renderer.renderCopyCentered(weapon5, NULL, 320, settings.screenHeight - 40);
	}

	renderer.renderCopyCentered(playerFaces, &faceClip, 768, settings.screenHeight - 50, 2, 2);
	renderer.renderCopyCentered(*healthTexture, NULL, 60, settings.screenHeight - 40);
	renderer.renderCopyCentered(*livesTexture, NULL, 140, settings.screenHeight - 40);
	renderer.renderCopyCentered(*ammoTexture, NULL, settings.screenWidth - 60, settings.screenHeight - 40);
	renderer.renderCopyCentered(*scoreTexture, NULL, settings.screenWidth - 60, settings.screenHeight - 100);
}
