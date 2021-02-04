#ifndef TILE_H
#define TILE_H
#include <SDL2/SDL.h>

class Tile {
  public:
    const SDL_Rect* clip;

    explicit Tile(const SDL_Rect* clip):
      clip(clip) {}
    ~Tile() {}

    const SDL_Rect getClip() const {
      return *clip;
    }

    // Usado para camuflar las puertas secretas
    const SDL_Rect* getClipPointer() const {
      return clip;
    }

    virtual void actualizar() = 0;
};

#endif  // TILE_H
