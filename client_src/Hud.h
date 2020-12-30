#ifndef HUD_H
#define HUD_H

#include <string>
#include "Player.h"
#include "ClientSettings.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlFont.h"

class Hud {
	class SdlRenderer& renderer;
	class SdlFont& font;
	const class Player& player;
	class SdlTexture* bulletsTexture;
	class SdlTexture* healthTexture;
	int cantBalas;
	int cantVida;
	// int cantPuntos;
	void actualizarBalas();
	void actualizarVida();

	// Llama a las funciones de actualizacion
	void actualizar();
	public:
		Hud(class SdlRenderer& renderer, class SdlFont& font, const class Player& player);

		~Hud();
		void renderizar(const class ClientSettings& settings);
};

#endif  // HUD_H
