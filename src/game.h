#ifndef GAME_H
#define GAME_H

#include <random>
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
  size_t _screen_width;
  size_t _screen_height;

  Spaceship _player;

  std::vector<Fire> _player_fire;
  bool _is_player_fire;
  
  std::vector<Alien> _aliens;
  Direction _direction{Direction::kRight};
  int _aliens_forces;

  std::vector<Fire> _alien_fire;
  
  int score{0};
};

#endif
