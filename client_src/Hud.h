#ifndef HUD_H
#define HUD_H

#include <string>
#include <vector>
#include "Player.h"
#include "ClientSettings.h"
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "SDLWrappers/SdlFont.h"

class Hud {
	const SDL_Color c_green = {34, 214, 15};
	const SDL_Color c_yellow = {204, 213, 19};
	const SDL_Color c_red = {226, 18, 18};
	SDL_Color c_rectangleScreen;
	Uint8 rectangleScreen_alpha;

	class SdlRenderer& renderer;
	class SdlFont& font;
	const class Player& player;
	class SdlTexture* ammoTexture;
	class SdlTexture* healthTexture;
	class SdlTexture* scoreTexture;
	class SdlTexture* livesTexture;
	std::vector<bool> displayWeapons;

	SDL_Rect faceClip;
	float playerFaceAnimation;
	int playerWaitAnimation;
	class SdlTexture playerFaces;
	class SdlTexture weapon1;
	class SdlTexture weapon2;
	class SdlTexture weapon3;
	class SdlTexture weapon4;
	class SdlTexture weapon5;
	int displayHealth;
	int displayAmmo;
	int displayScore;
	int displayLives;

	void actualizarAmmo();
	void actualizarHealth();
	void actualizarLives();
	void actualizarScore();
	void actualizarWeapons();
	void actualizarFaceBlood();
	void actualizarFaceAnimation();
	// Llama a las funciones de actualizacion
	void actualizar();
	public:
		Hud(class SdlRenderer& renderer, class SdlFont& font, const class Player& player);

		~Hud();
		void renderizar(const class ClientSettings& settings);
};

#endif  // HUD_H
