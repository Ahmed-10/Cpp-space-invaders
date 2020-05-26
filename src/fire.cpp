#include "fire.h"

Fire::Fire(int screen_width, int screen_height, Spaceship player)
    : _screen_width(screen_width) 
    , _screen_height(screen_height)
{
    _direction = Direction::kUp;
    pos_x = player.pos_x + 20;
    pos_y = player.pos_y - 20;
}

Fire::Fire(int screen_width, int screen_height, Alien alien, size_t alien_num)
    : _screen_width(screen_width)
    , _screen_height(screen_height)
{
    _direction = Direction::kDown;
    pos_x = alien._matrix_pos_x[alien_num];
    pos_y = alien._matrix_pos_y[alien_num] + 2;
}

void Fire::UpdatePosition(){
    switch (_direction)
    {
    case Direction::kUp:
        pos_y -= 4;
        break;
    case Direction::kDown:
        pos_y += 4;
        break;
    default:
        break;
    }
}