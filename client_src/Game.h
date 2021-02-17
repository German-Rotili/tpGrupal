#ifndef GAME_H
#define GAME_H

#include <unistd.h>  // Para usleep
#include <vector>
#include <iostream>
#include <chrono>
#include "../common_src/SDLWrappers/SdlContext.h"
#include "client_helper.h"
#include "../common_src/BlockingQueueIntention.h"
#include "../common_src/ProtectedQueueAction.h"
#include "ThSender.h"
#include "ThRequester.h"
#include "World.h"
#include "ClientSettings.h"
#include "../common_src/Snapshot.h"

class Game {
  BlockingQueueIntention intentionsQueue;
  ProtectedQueueAction actionsQueue;
  ThRequester requester;
  ThSender sender;
  World& world;
  ClientSettings& settings;
  Snapshot updateSnapshot;
  std::vector<char> currentFrameIntentions;
  SDL_Event e;
  const Uint8* currentKeyStates;
  bool quit;

  void processInput();
  void sendIntentions();
  void updateWorld();

  public:
    Game(Client & client, World & world, ClientSettings & settings);
    ~Game();
    void loop();
};

#endif  // GAME_H
