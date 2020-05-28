#ifndef SPIRIT_H
#define SPIRIT_H

#include <iostream>

enum class Direction { kLeft, kRight, kUp, kDown};

class Spirit {
 public:

  int get_rank() { return _rank; }
  int get_x_pos() { return _x_pos; }
  int get_y_pos() { return _y_pos; }

  virtual void update_position() { std::cout << "update_position\n"; };
  // virtual void update_position() = 0;
 
 protected:
  int _rank;
  int _x_pos;
  int _y_pos;
};
#endif