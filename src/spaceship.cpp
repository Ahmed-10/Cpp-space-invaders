#include "spaceship.h"
#include <cmath>
#include <iostream>


Spaceship::Spaceship(int screen_width, int screen_height)
          : _screen_width(screen_width)
          , _screen_height(screen_height)
{
  _x_pos = screen_width / 2;
  _y_pos = screen_height;
}

Spaceship& Spaceship::operator = (Spaceship& source){
  if(this == &source) { return *this; }

  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;
  _screen_height = source._screen_height;
  _screen_width = source._screen_width;

  return *this;
}

void Spaceship::update_position(Direction direction) {
  switch (direction) {
    case Direction::kLeft:
      _x_pos -= 4;
      break;

    case Direction::kRight:
      _x_pos += 4;
      break;
  }

  // Wrap the Spaceship around to the beginning if going off of the screen.
  if(_x_pos < 0) { _x_pos = _screen_width - 41; }
  else if(_x_pos > (_screen_width - 40)) { _x_pos = 0; }
  else {}
}
