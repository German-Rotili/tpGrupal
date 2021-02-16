#ifndef SDLMUSIC_H
#define SDLMUSIC_H

#include "SdlContext.h"
#include <string>

class SdlMusic {
  Mix_Music* music;

	public:
		SdlMusic(std::string path);
		~SdlMusic();
		void play() const;
    void stop() const;
};

#endif  // SDLMUSIC_H
