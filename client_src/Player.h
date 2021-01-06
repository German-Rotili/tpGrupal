#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "SDLWrappers/SdlTexture.h"
#include "SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"

class Player {
	SdlRenderer& renderer;
	const SdlTexture texture;
  float x;
  float y;
  float direction;
  float health;
	int score;
	int lives;
	int idArmaActual;

	SDL_Rect weaponClip;
  float frameActual;
  int cantFrames;

	const int DRAW_WEAPON_X;
	const double DRAW_SCALE;
	const int DRAW_WEAPON_Y;
	const double animationSpeed;

	PlayerWeapon* armaActual;
	PlayerWeapon* cuchillo;
	PlayerWeapon* pistola;
	PlayerWeapon* ametralladora;
	PlayerWeapon* canionDeCadena;
	PlayerWeapon* lanzacohetes;

	public:
		bool animarArma;
		Player(SdlRenderer& renderer, const ClientSettings& settings, float xInicial,
			float yInicial, float dirInicial, float healthInicial, int scoreInicial,
			int livesInicial);
		~Player();

		float getX() const;
		float getY() const;
		float getDirection() const;
		int getHealth() const;
		int getIdArmaActual() const;
		int getCantBalasArmaActual() const;
		int getScore() const;
		int getLives() const;
		std::vector<bool> getArmasDisponibles() const;

		void setPosicion(float x, float y);
		void setDirection(float direction);
		void setHealth(float health);
		void setScore(int score);
		void setLives(int lives);
		void setArmaActual(int idArma);

    void renderizar(ClientSettings& settings);
};

#endif  // PLAYER_H
