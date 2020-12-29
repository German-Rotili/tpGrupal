#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SdlException.h"
#include "SdlTexture.h"

class SdlRenderer {
  friend class SdlTexture;
  friend class SdlFont;
  public:
    SDL_Renderer* renderer;
    explicit SdlRenderer(SDL_Renderer* renderer);
    SdlRenderer(const SdlRenderer&) = delete;
    SdlRenderer& operator=(const SdlRenderer&) = delete;
    SdlRenderer& operator=(SdlRenderer&& other);
    SdlRenderer(SdlRenderer&& other);
    ~SdlRenderer();
    void setRenderDrawColor(int r, int g, int b, int a);
    void renderDrawLine(int x1, int y1, int x2, int y2);
    void renderDrawRect(int x, int y, int w, int h);
    void renderFillRect(int x, int y, int w, int h);
    void renderClear();
    void renderPresent();
    void renderDrawPoint(int x, int y);
    void renderCopy(const class SdlTexture& texture,
      const SDL_Rect* clip, int x, int y, double xscale = 1, double yscale = 1);

    void renderCopyCentered(const class SdlTexture& texture,
      const SDL_Rect* clip, int x, int y, double xscale = 1, double yscale = 1);
};

#endif  // SDLRENDERER_H
