#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "spirit.h"

class Spaceship : public Spirit{
 public:
  Spaceship(){}
  Spaceship(int screen_width, int screen_hight);

  Spaceship(Spaceship& soruce);
  Spaceship& operator = (Spaceship& source);

  Spaceship(Spaceship&& soruce);
  Spaceship& operator = (Spaceship&& source);

  void update_position(Direction direction);

 private:
  int _screen_width;
  int _screen_height;

  static std::mutex _mtx;
};

#endif