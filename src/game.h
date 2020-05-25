#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL2/SDL.h"
#include "renderer.h"
#include "spaceship.h"
#include "alien.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height, int aliens_forces)
    : _spirit(screen_width, screen_height) 
    , _aliens(screen_width, screen_height, aliens_forces) {}
    
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;

 private:
  Spaceship _spirit;
  Alien _aliens;
  int score{0};
};

#endif
