#ifndef PLAYER_H
#define PLAYER_H

#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"

class Player {
	const SdlTexture& texture;
  float x;
  float y;
  float direction;
  float health;
	int idArmaActual;
  SDL_Rect weaponClip;
  float frameActual;
  int cantFrames;
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
		float getX() const;
		float getY() const;
		float getDirection() const;

		int getHealth() const;
		//int getCantBalas();

		void setPosicion(float x, float y);
		void setDirection(float direction);
		void setHealth(float health);
		// Provisorio?
		void setArmaActual(int idArma);
    void renderizar(SdlRenderer& renderer, ClientSettings& settings);
};

#endif  // PLAYER_H
