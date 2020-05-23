#include "spaceship.h"
#include <cmath>
#include <iostream>


Spaceship::Spaceship(int screen_width, int screen_height)
          : _screen_width(screen_width),
            _screen_height(screen_height),
            pos_x(screen_width / 2),
            pos_y(screen_height){}


void Spaceship::UpdatePosition(Direction direction) {
  switch (direction) {
    case Direction::kLeft:
      pos_x -= 4;
      std::cout << pos_x << std::endl;
      break;

    case Direction::kRight:
      pos_x += 4;
      std::cout << pos_x << std::endl;
      break;
  }

  // Wrap the Spaceship around to the beginning if going off of the screen.
  if(pos_x < 0) { pos_x = _screen_width - 41; }
  else if(pos_x > (_screen_width - 40)) { pos_x = 0; }
  else {}
}
