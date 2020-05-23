#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Spaceship {
 public:
  enum class Direction { kLeft, kRight };

  Spaceship(int screen_width, int screen_hight);
  int pos_x;
  int pos_y ;

  void UpdatePosition(Direction direction);

 private:
  int _screen_width;
  int _screen_height;
};

#endif