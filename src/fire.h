#ifndef FIRE_H
#define FIRE_H

#include "spaceship.h"
#include "alien.h"
#include <iostream>


class Fire {
 public:
    Fire(int screen_width, int screen_height, Spaceship player);
    Fire(int screen_width, int screen_height, Alien alien, size_t alien_num);

    int pos_x;
    int pos_y;

    void UpdatePosition();

 private:
    int _screen_width;
    int _screen_height;

    Direction _direction;
};
#endif