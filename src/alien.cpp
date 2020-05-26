#include "alien.h"
#include <iostream>


Alien::Alien(int screen_width, int screen_height, int aliens_forces)
          : _screen_width(screen_width),
            _screen_height(screen_height),
            _aliens_forces(aliens_forces)
{
  _direction = Direction::kRight;
  int x = screen_width / 8;
  int y = screen_height / 10;
  int pos_x = x, pos_y = y;
  
  for(size_t i = 1; i <= aliens_forces; i++){
    _matrix_pos_x.emplace_back(pos_x);
    _matrix_pos_y.emplace_back(pos_y);
    pos_x += 40;
    
    if(i % 10 == 0){
    	pos_x = x;
    	pos_y += 56;	
    }

    _matrix.push_back(true);
  }
}


void Alien::UpdatePosition() {
  switch (_direction) {
    case Direction::kLeft:
      for (size_t i = 0; i < _aliens_forces; i++)
      {
        _matrix_pos_x[i] -= 1; 
      }
      break;
    case Direction::kRight:
      for (size_t i = 0; i < _aliens_forces; i++)
      {
        _matrix_pos_x[i] += 1; 
      }
      break;        
    default:
      break;
  }

// Wrap the Alien back at the beginning and at the end if going off of the screen.
  if(_matrix_pos_x[0] < 0) { 
      _direction = Direction::kRight;

      for (size_t i = 0; i < _aliens_forces; i++)
      {
        _matrix_pos_y[i] += 2; 
      }
    }
  else if(_matrix_pos_x[_aliens_forces - 1] > (_screen_width - 40)) { 
      _direction = Direction::kLeft;
      
      for (size_t i = 0; i < _aliens_forces; i++)
      {
        _matrix_pos_y[i] += 2; 
      }
    }
  else {}
}
