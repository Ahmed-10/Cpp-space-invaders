#include "alien.h"
#include <random>


Alien::Alien(int x, int y)
{
  _x_pos = x;
  _y_pos = y;

  std::random_device dev;
  std::mt19937 engine(dev());
  std::uniform_int_distribution<int> random(0, 3);

  _rank = random(engine);

}


void Alien::update_position(Direction direction) {
  switch (direction) {
    case Direction::kLeft:
        _x_pos -= 1; 
      break;
    case Direction::kRight:
        _x_pos += 1; 
      break;
    case Direction::kDown:
      _y_pos += 2;
      break;        
    default:
      break;
  }
}
