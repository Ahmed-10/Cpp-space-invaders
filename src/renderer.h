#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include <random>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "spaceship.h"
#include "alien.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, int aliens_forces);
  ~Renderer();

  void Render(Spaceship const spirit, Alien const aliens);
  void UpdateWindowTitle();

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *sdl_texture_spaceship;
  std::vector<SDL_Texture*> sdl_texture_aliens;

  // std::random_device _dev;
  // std::mt19937 _engine;
  // std::uniform_int_distribution<int> _random;

  int _aliens_forces;
  std::vector<std::string> _aliens_imgs = {"../gfx/alien1.png", 
                                           "../gfx/alien2.png", 
                                           "../gfx/alien3.png", 
                                           "../gfx/alien4.png"};

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
