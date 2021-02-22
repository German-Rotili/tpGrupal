#include "Game.h"

Game::Game(Client & client, World & world, ClientSettings & settings):
  requester(client, actionsQueue),
  sender(client, intentionsQueue),
  world(world),
  settings(settings),
  currentKeyStates(SDL_GetKeyboardState(NULL)),
  gameStarted(false),
  quit(false) {
    requester.start();
    sender.start();
}

Game::~Game() {
  requester.stop();
  requester.join();
  this->intentionsQueue.close_queue();
  sender.stop();
  sender.join();
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
  while (!quit && this->requester.is_active()) {
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    processInput();
    if (gameStarted) {
      sendIntentions();
      updateWorld();
    } else {  // En cada frame chequeo si el requester ya obtuvo id valida.
      int obtainedId = requester.getObtainedId();
      if (obtainedId != INVALID_ID) {  // Si la obtuvo empiezo el juego
        settings.myCurrentId = obtainedId;
        gameStarted = true;
      } else {
        // no hago nada, sigo esperando a que el juego comience.
      }
    }
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
