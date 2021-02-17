#include "SdlMusic.h"
#include <string>

SdlMusic::SdlMusic(std::string path) {
	music = Mix_LoadMUS(path.c_str());;
	if (music == NULL) {
		char error[BUF_SIZE];
    snprintf(error, sizeof(error),
		 "Unable to load music %s! Mix_GetError: %s\n", path.c_str(), Mix_GetError());
		throw SdlException(error);
  }
}

SdlMusic::~SdlMusic() {
	if (music != NULL) {
		Mix_FreeMusic(music);
  	music = NULL;
	}
}

void SdlMusic::play() const {
	// detengo musica si la hay:
	this->stop();
	// Reproduzco esta musica:
	Mix_VolumeMusic(0);
	Mix_PlayMusic(this->music, -1);
}


void SdlMusic::stop() const {
	// Si hay musica reproduciendose:
	if (Mix_PlayingMusic() != 0) {
		// La detengo
		Mix_HaltMusic();
	}
}
