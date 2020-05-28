#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include <random>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, int aliens_forces);
  ~Renderer();

  void Render_spirit(int const x, int const y);
  void Render_spirit_fire(int const x, int const y);
  void Render_aliens(int const x, int const y, int const rank);
  void Render_aliens_fire(int x, int y, int rank);

  void Clear_screen(void);
  void Update_screen(void);
             
  void UpdateWindowTitle(void);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *sdl_texture_spaceship;
  SDL_Texture *sdl_texture_player_fire;
  std::vector<SDL_Texture*> sdl_texture_aliens;
  std::vector<SDL_Texture*> sdl_texture_aliens_fires;

  std::vector<std::string> _aliens_imgs = {"../gfx/alien1.png", 
                                           "../gfx/alien2.png", 
                                           "../gfx/alien3.png", 
                                           "../gfx/alien4.png"};

  std::vector<std::string> _aliens_fire_imgs = {"../gfx/shoot1.png", 
                                                "../gfx/shoot2.png", 
                                                "../gfx/shoot3.png", 
                                                "../gfx/shoot4.png"};

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
