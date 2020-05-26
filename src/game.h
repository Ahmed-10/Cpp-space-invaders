#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL2/SDL.h"
#include "renderer.h"
#include "spaceship.h"
#include "alien.h"
#include "fire.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height, int aliens_forces);
    
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;

 private:
  int _screen_width;
  int _screen_height;
  int k = 1;
  Spaceship _spirit;
  Alien _aliens;
  int _aliens_forces;

  std::vector<Fire> _player_fire;
  bool _is_spirit_fire;

  std::vector<Fire> _alien_fire;
  int score{0};
};

#endif
