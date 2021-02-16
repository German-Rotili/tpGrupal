#ifndef SDLSOUND_H
#define SDLSOUND_H

#include "SdlContext.h"
#include <string>

class SdlSound {
  Mix_Chunk* sound;

	public:
		SdlSound(std::string path);
		~SdlSound();
		void play(int channel, int times) const;
		void playInPosition(int channel, int times, int angle, int distance) const;
};

#endif  // SDLSOUND_H
