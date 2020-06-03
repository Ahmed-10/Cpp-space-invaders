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

Alien::Alien(Alien& source){
  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;
}

Alien& Alien::operator = (Alien& source){
  if(this == &source) { return *this; }

  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;

  return *this;
}

Alien::Alien(Alien&& source){
  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;

}

Alien& Alien::operator = (Alien&& source){
  if(this == &source) { return *this; }

  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;

  return *this;
}

void Alien::update_position(Direction direction) {
  switch (direction) {
    case Direction::kLeft:
        _x_pos -= 2; 
      break;
    case Direction::kRight:
        _x_pos += 2; 
      break;
    case Direction::kDown:
      _y_pos += 4;
      break;        
    default:
      break;
  }
}
