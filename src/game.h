#ifndef GAME_H
#define GAME_H

#include <memory>
#include <utility>
#include <random>
#include <mutex>

#include "renderer.h"
#include "spaceship.h"
#include "alien.h"
#include "fire.h"

class Game {
 public:
  Game(Renderer* renderer, std::size_t screen_width, std::size_t screen_height, int aliens_forces);

  bool start(std::size_t target_frame_duration);
  bool Run(std::size_t target_frame_duration);
  bool end(std::size_t target_frame_duration);
  
  int get_score();
  int get_lifes();

 private:
  Renderer* _renderer;

  int _screen_width;
  int _screen_height;
  int _aliens_forces;
  bool _running;
  bool _return;
  
  std::mutex _player_mtx;
  std::mutex _aliens_mtx;

  void draw_spaceship();
  void draw_aliens();
  void draw_spaceship_fire();
  void draw_aliens_fire();

  void add_spaceship_fire();
  
  void update_spaceship();
  void update_aliens();
  void update_spaceship_fire();
  void update_aliens_fire();

  void event_handle();

  std::unique_ptr<Spaceship> _player;
  std::vector<std::unique_ptr<Fire>> _player_fire;
  std::vector<std::unique_ptr<Alien>> _aliens;
  Direction _direction{Direction::kRight};
  std::vector<std::unique_ptr<Fire>> _aliens_fire;

  int go_right{0};
  int go_left{0};

  int _score{0};
  int _lifes{3};
};

#endif
