#include "Hud.h"
#include <string>
#include <cmath>
#include "Player.h"
#include "ClientSettings.h"
#include "../common_src/pathsAssets.h"
#include "../common_src/SDLWrappers/SdlTexture.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "../common_src/SDLWrappers/SdlFont.h"

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
	font(FONT_HUD_PATH, FONT_SIZE),
	player(player),
	faceClip({25, 0, 24, 32}),
	faceScale(double(settings.screenWidth) * 0.001953),
	playerFaces(renderer, PLAYER_FACES_PATH),
	weapon1(renderer, font, "1", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon2(renderer, font, "2", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon3(renderer, font, "3", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon4(renderer, font, "4", c_yellow.r, c_yellow.g, c_yellow.b),
	weapon5(renderer, font, "5", c_yellow.r, c_yellow.g, c_yellow.b),
	ammoIcon(renderer, AMMO_ICON_PATH),
	liveIcon(renderer, LIVE_ICON_PATH),
	sndHurt(SND_HURT_PATH),
	sndHealing(SND_HEALING_PATH),
	sndScoreup(SND_SCOREUP_PATH),
	sndPickAmmo(SND_PICKAMMO_PATH) {
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
		ammoIcon.setColorMod(c_yellow.r, c_yellow.g, c_yellow.b);
		liveIcon.setColorMod(c_green.r, c_green.g, c_green.b);
		update();
		rectangleScreen_alpha = 0;
}

Hud::~Hud() {
	delete ammoTexture;
	delete healthTexture;
	delete scoreTexture;
	delete livesTexture;
}

void Hud::updateFaceBlood() {
	if (displayHealth <= 0) {
		faceClip.y = 33*6;
	} else if (displayHealth >= 100) {
		faceClip.y = 0;
	} else {
		faceClip.y = 33 * static_cast<int>((100-displayHealth)*7/100);
	}
}
void Hud::updateFaceAnimation() {
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

void Hud::updateAmmo() {
	int auxAmmo = player.getCantBalas();
	if (auxAmmo != displayAmmo) {
		if (auxAmmo > displayAmmo) {
			c_rectangleScreen = c_yellow;
			rectangleScreen_alpha = 240;
			sndPickAmmo.play(-1, 0);
		}
		displayAmmo = auxAmmo;
		delete ammoTexture;
		ammoTexture = new SdlTexture(renderer, font,
			std::to_string(displayAmmo), c_yellow.r, c_yellow.g, c_yellow.b);
	}
}

void Hud::updateHealth() {
	int auxHealth = player.getHealth();
	if (auxHealth < displayHealth) {
		c_rectangleScreen = c_red;
		sndHurt.play(-1, 0);
	} else if (auxHealth > displayHealth) {
		c_rectangleScreen = c_green;
		sndHealing.play(-1, 0);
	} else {
		return;
	}
	rectangleScreen_alpha = 240;
	displayHealth = auxHealth;
	delete healthTexture;
	healthTexture = new SdlTexture(renderer, font,
		"+" + std::to_string(displayHealth), c_green.r, c_green.g, c_green.b);
	updateFaceBlood();
}

void Hud::updateScore() {
	int auxScore = player.getScore();
	if (auxScore != displayScore) {
		if (auxScore > displayScore) {
			c_rectangleScreen = c_yellow;
			rectangleScreen_alpha = 240;
			sndScoreup.play(-1, 0);
		}
		displayScore = auxScore;
		delete scoreTexture;
		scoreTexture = new SdlTexture(renderer, font,
			"$ " +std::to_string(displayScore), c_yellow.r, c_yellow.g, c_yellow.b);
	}
}

void Hud::updateLives() {
	int auxLives = player.getLives();
	if (auxLives != displayLives) {
		displayLives = auxLives;
		delete livesTexture;
		livesTexture = new SdlTexture(renderer, font,
			std::to_string(displayLives), c_green.r, c_green.g, c_green.b);
	}
}

void Hud::updateWeapons() {
	displayWeapons = player.getArmasDisponibles();
}

void Hud::update() {
	if (rectangleScreen_alpha > 0) {
		rectangleScreen_alpha -= 20;
	}
	updateHealth();
	updateAmmo();
	updateScore();
	updateLives();
	updateWeapons();
	updateFaceAnimation();
}

void Hud::render(const ClientSettings & settings) {
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

	renderer.renderCopyCentered(liveIcon, NULL, COLUMNA2-(*livesTexture).getWidth(), FILA2, faceScale, faceScale);
	renderer.renderCopyCentered(*livesTexture, NULL, COLUMNA2, FILA2);

	if (!player.getIdArmaActual() == 0) {
		renderer.renderCopyCentered(ammoIcon, NULL, COLUMNA5-(weapon1).getWidth()*4, FILA2, faceScale, faceScale);
		renderer.renderCopyCentered(*ammoTexture, NULL, COLUMNA5, FILA2);
	}
	renderer.renderCopyCentered(*scoreTexture, NULL, COLUMNA5, FILA1);
}
