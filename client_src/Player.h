#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../common_src/SDLWrappers/SdlTexture.h"
#include "../common_src/SDLWrappers/SdlSound.h"
#include "../common_src/SDLWrappers/SdlRenderer.h"
#include "ClientSettings.h"
#include "PlayerWeapon.h"
#include "ResourcesLoader.h"

class Player {
	SdlRenderer& renderer;
	const SdlTexture texture;
  double x;
  double y;
  double direction;
  double health;
	int score;
	int lives;
	int idArmaActual;

	SDL_Rect weaponClip;
  double frameActual;
  int cantFrames;

	const int DRAW_WEAPON_X;
	const double DRAW_SCALE;
	const int DRAW_WEAPON_Y;
	const double animationSpeed;

	PlayerWeapon cuchillo;
	PlayerWeapon pistola;
	PlayerWeapon ametralladora;
	PlayerWeapon canionDeCadena;
	PlayerWeapon lanzacohetes;

	SdlSound& sndDying;
	PlayerWeapon* armaActual;
	int cantBalas;

	public:
		bool animarArma;
		Player(SdlRenderer& renderer, ResourcesLoader& src, const ClientSettings& settings, double xInicial,
			double yInicial, double dirInicial, double healthInicial, int scoreInicial,
			int livesInicial);
		~Player();

		double getX() const;
		double getY() const;
		double getDirection() const;
		double getDistanceToPoint(double x, double y) const;
		int getHealth() const;
		int getIdArmaActual() const;
		int getCantBalas() const;
		int getScore() const;
		int getLives() const;
		std::vector<bool> getArmasDisponibles() const;

		void setPosicion(double x, double y);
		void setDirection(double direction);
		void setHealth(double health);
		void setScore(int score);
		void setLives(int lives);
		void setArmaActual(int idArma);
		void setShootingAction();
		void setCantBalas(int cantBalas);

    void renderizar(ClientSettings& settings);
};

#endif  // PLAYER_H
