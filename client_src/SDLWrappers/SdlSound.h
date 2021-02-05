#ifndef SDLSOUND_H
#define SDLSOUND_H

#include "SdlContexto.h"
#include <string>

class SdlSound {
  Mix_Chunk* sound;

	public:
		SdlSound(std::string path);
		~SdlSound();
		int play(int channel, int times) const;
		void setVolume(int volume); // de 0 a 128
};

#endif  // SDLSOUND_H
