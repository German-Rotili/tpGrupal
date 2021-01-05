#include "SdlWindow.h"
#include <string>
#include <utility>

SdlWindow::SdlWindow(std::string nombre, int width, int height) {
  this->window = SDL_CreateWindow(nombre.c_str(), SDL_WINDOWPOS_UNDEFINED,
  SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    char error[BUF_SIZE];
    snprintf(error, sizeof(error), "Error en Window . SDL_Error: %s\n", SDL_GetError());
    throw SdlException(error);
  }
}

SdlWindow::~SdlWindow() {
  SDL_DestroyWindow(this->window);
}

SdlRenderer SdlWindow::getRenderer() {
  SdlRenderer resultado(
    SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED));
  return std::move(resultado);
}
