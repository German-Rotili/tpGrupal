#include "Hud.h"
#include <string>
#include "Player.h"
#include "ClientSettings.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlFont.h"
Hud::Hud(class SdlRenderer& renderer, class SdlFont& font, const class Player& player):
	renderer(renderer),
	font(font),
	player(player) {
		cantBalas = player.getHealth();
		cantVida = player.getHealth();
		bulletsTexture = new SdlTexture(renderer, font,
			std::to_string(cantBalas), 100, 255, 100);
		healthTexture = new SdlTexture(renderer, font,
			std::to_string(cantVida), 100, 255, 100);
}

Hud::~Hud() {
	delete bulletsTexture;
	delete healthTexture;
}

void Hud::actualizar() {
	actualizarBalas();
	actualizarVida();
}



void Hud::actualizarBalas() {
	int auxBalas = player.getHealth();
	if (auxBalas != cantBalas) {
		printf("Balas actualizadas\n");
		cantBalas = auxBalas;
		delete bulletsTexture;
		bulletsTexture = new SdlTexture(renderer, font,
			std::to_string(cantBalas), 100, 255, 100);
	}
}

void Hud::actualizarVida() {
	int auxVida = player.getHealth();
	if (auxVida != cantVida) {
		printf("Vida actualizada\n");
		cantVida = auxVida;
		delete healthTexture;
		healthTexture = new SdlTexture(renderer, font,
			std::to_string(cantVida), 100, 255, 100);
	}
}

void Hud::renderizar(const ClientSettings & settings) {
	this->actualizar();
	renderer.renderCopy(*bulletsTexture, NULL, 60, settings.screenHeight - 80);
}
