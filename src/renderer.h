#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include <random>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "spaceship.h"
#include "alien.h"
#include "fire.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, int aliens_forces);
  ~Renderer();

  void Render(Spaceship const spirit, Alien const aliens
             , std::vector<Fire> alien_fire);

  void Render_spirit_fire(int fire_x, int fire_y);

  void Clear_screen(void);
  void Update_screen(void);
             
  void UpdateWindowTitle(void);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *sdl_texture_spaceship;
  SDL_Texture *sdl_texture_player_fire;
  std::vector<SDL_Texture*> sdl_texture_aliens;

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
