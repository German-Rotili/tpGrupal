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

int SdlSound::play(int channel, int times) const {
	return Mix_PlayChannel(channel, sound, times);
}

void SdlSound::setVolume(int volume) {
	Mix_VolumeChunk(sound, volume);
}
