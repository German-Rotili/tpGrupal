#ifndef PLAYER_H
#define PLAYER_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"

class Player {
	const SdlTexture& texture;
  float vida;
  float x;
  float y;
  float direction;
  float health;
	int idArmaActual;
  SDL_Rect weaponClip;
  float frameActual;
  int maxFrame;
	float drawScale;
	PlayerWeapon* cuchillo;
	PlayerWeapon* pistola;
	PlayerWeapon* ametralladora;
	PlayerWeapon* canionDeCadena;
	PlayerWeapon* lanzacohetes;

	public:
		bool animarArma;
		Player(const SdlTexture& texture, float xInicial, float yInicial, float dirInicial, float vidaInicial);
		~Player();
		float getX();
		float getY();
		float getDirection();

		void actualizarPosicion(float x, float y);
		void actualizarDireccion(float direction);
		void actualizarVida(float health);
		// Provisorio?
		void actualizarArmaActual(int idArma);
    void renderizar(SdlRenderer& renderer, ClientSettings& settings);
};

#endif  // PLAYER_H
