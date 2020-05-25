#ifndef ALIEN_H
#define ALIEN_H

#include <vector>
#include <utility>

enum class Direction { kLeft, kRight};

class Alien {
 public:
  Alien(int screen_width, int screen_height, int aliens_forces);

  std::vector<bool> _matrix;
  std::vector<std::pair<int , int>> _matrix_pos;

  void UpdatePosition();

 private:
  int _aliens_forces;
  int _screen_width;
  int _screen_height;
  Direction _direction;
};
#endif