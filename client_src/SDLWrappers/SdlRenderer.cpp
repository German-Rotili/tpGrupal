#include "SdlRenderer.h"
#include <string>

SdlRenderer::SdlRenderer(SDL_Renderer* renderer) {
  this->renderer = renderer;
  if (this->renderer == NULL) {
    char* error;
    sprintf(error, "Error en Renderer . SDL_Error: %s\n", SDL_GetError());
    throw SdlException(error);
  }
}

SdlRenderer::SdlRenderer(SdlRenderer&& other) {
  if (this == &other) return;
  this->renderer = other.renderer;
  other.renderer = NULL;
}


SdlRenderer& SdlRenderer::operator=(SdlRenderer&& other) {
  if (this == &other) return *this;
  if (this->renderer != NULL) SDL_DestroyRenderer(this->renderer);
  this->renderer = other.renderer;
  other.renderer = NULL;
  return *this;
}

SdlRenderer::~SdlRenderer() {
  SDL_DestroyRenderer(this->renderer);
}

void SdlRenderer::setRenderDrawColor(int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SdlRenderer::renderDrawLine(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void SdlRenderer::renderPresent() {
  SDL_RenderPresent(renderer);
}
void SdlRenderer::renderFillRect(int x, int y, int w, int h) {
  SDL_Rect rectangulo = {x, y, w, h};
  SDL_RenderFillRect(renderer, &rectangulo);
}

void SdlRenderer::renderClear() {
  SDL_RenderClear(renderer);
}

void SdlRenderer::renderDrawPoint(int x, int y) {
  SDL_RenderDrawPoint(renderer, x, y);
}

void SdlRenderer::renderCopy(const SdlTexture& texture,
  const SDL_Rect* clip, int x, int y, int xscale, int yscale) {
    SDL_Rect renderQuad = {x, y, texture.width, texture.height};
    if (clip) {
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
    }
    renderQuad.w *= xscale;
    renderQuad.h *= yscale;
    SDL_RenderCopy(renderer, texture.texture, clip, &renderQuad);
  }
