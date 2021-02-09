#include "SdlSound.h"
#include <string>

SdlSound::SdlSound(std::string path) {
	sound = Mix_LoadWAV(path.c_str());;
	if (sound == NULL) {
		char error[BUF_SIZE];
    snprintf(error, sizeof(error),
		 "Unable to load font %s! SDL_ttf Error: %s\n", path.c_str(), Mix_GetError());
		throw SdlException(error);
  }
}

SdlSound::~SdlSound() {
	if (sound != NULL) {
		Mix_FreeChunk(sound);
  	sound = NULL;
	}
}

void SdlSound::play(int channel, int times) const {
	Mix_PlayChannel(channel, sound, times);
}

void SdlSound::playInPosition(int channel, int times, int angle, int distance)
const {
	// angle 135 sería atras a la izquierda
	int retChannel = Mix_PlayChannel(channel, sound, times);
	if(!Mix_SetPosition(retChannel, angle, distance)) {
    printf("Mix_SetPosition: %s\n", Mix_GetError());
    // no position effect, is it ok?
	}
}
