#ifndef ALIEN_H
#define ALIEN_H

#include "spirit.h"

class Alien : public Spirit{
 public:
  Alien(int x, int y);

  void update_position(Direction direction);
};
#endif