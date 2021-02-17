#include "Game.h"

Game::Game(Client & client, World & world, ClientSettings & settings):
  requester(client, actionsQueue),
  sender(client, intentionsQueue),
  world(world),
  settings(settings),
  currentKeyStates(SDL_GetKeyboardState(NULL)),
  quit(false) {
    requester.start();
    sender.start();
}

Game::~Game() {
  // Hacer join de requester y sender?
}

void Game::processInput() {
  currentFrameIntentions.clear();
  // Event Loop
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_1:
        currentFrameIntentions.push_back(SDLK_1);
        break;
        case SDLK_2:
        currentFrameIntentions.push_back(SDLK_2);
        break;
        case SDLK_3:
        currentFrameIntentions.push_back(SDLK_3);
        break;
        case SDLK_4:
        currentFrameIntentions.push_back(SDLK_4);
        break;
        case SDLK_5:
        currentFrameIntentions.push_back(SDLK_5);
        break;
        case SDLK_e:
        currentFrameIntentions.push_back(SDLK_e);
        break;
      }
    }
  }
  if (currentKeyStates[SDL_SCANCODE_W]) {
    currentFrameIntentions.push_back('w');
  }
  if (currentKeyStates[SDL_SCANCODE_S]) {
    currentFrameIntentions.push_back('s');
  }
  if (currentKeyStates[SDL_SCANCODE_A ]) {
    currentFrameIntentions.push_back('a');
  }
  if (currentKeyStates[SDL_SCANCODE_D ]) {
    currentFrameIntentions.push_back('d');
  }
  if (currentKeyStates[SDL_SCANCODE_SPACE ]) {
    currentFrameIntentions.push_back(' ');
  }
}

void Game::sendIntentions() {
  if (currentFrameIntentions.size() > 0) {
    Intention intention_aux(settings.myCurrentId, currentFrameIntentions);
    intentionsQueue.add_element(intention_aux);
  }
}

void Game::updateWorld() {
  updateSnapshot = requester.get_snapshot();
  world.update(updateSnapshot, actionsQueue);
  world.render(settings);
}

void Game::loop() {
  while (!quit) {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    processInput();
    sendIntentions();
    updateWorld();
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    int sleep_time = 1000000/settings.fps - elapsed_microseconds;
    if (sleep_time > 0) {
      usleep(1000000/settings.fps - elapsed_microseconds);
    } else {
      std::cout << "Bajada de FPS" << std::endl;
    }
  }
}
