#include "fire.h"

Fire::Fire(int x, int y)
{
    _direction = Direction::kUp; 
    _rank = 0;
    _x_pos = x;
    _y_pos = y;
}

Fire::Fire(int x, int y, int rank)
{
    _direction = Direction::kDown;
    _x_pos = x;
    _y_pos = y;
    _rank = rank;
}

Fire::Fire(Fire& source){
  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;
}

Fire& Fire::operator = (Fire& source){
  if(this == &source) { return *this; }

  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;

  return *this;
}

Fire::Fire(Fire&& source){
  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;

}

Fire& Fire::operator = (Fire&& source){
  if(this == &source) { return *this; }

  _x_pos = source._x_pos;
  _y_pos = source._y_pos;
  _rank = source._rank;

  return *this;
}

void Fire::update_position(){
    switch (_direction)
    {
    case Direction::kUp:
        _y_pos -= 1;
        break;
    case Direction::kDown:
        _y_pos += 4;
        break;
    default:
        break;
    }
}