#ifndef FIRE_H
#define FIRE_H

#include "spirit.h"

class Fire : public Spirit{

 public:
  Fire(int x, int y);
  Fire(int x, int y, int rank);

  void update_position();

 private:
  Direction _direction;
};
#endif