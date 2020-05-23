#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL2/SDL.h"
#include "renderer.h"
#include "spaceship.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height)
    : _spirit(screen_width, screen_height) {}
    
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;

 private:
  Spaceship _spirit;

  int score{0};
};

#endif
