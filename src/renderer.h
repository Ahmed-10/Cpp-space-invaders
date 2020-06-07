#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include <random>
#include <mutex>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, int aliens_forces);
  ~Renderer();

  void Render_game_name();
  void Render_play_opt();
  void Render_quit_opt();

  void Render_play_again(int score);
  void Render_exit(int score);

  void Render_spirit(int const x, int const y);
  void Render_spirit_fire(int const x, int const y);
  void Render_aliens(int const x, int const y, int const rank);
  void Render_aliens_fire(int const x, int const y, int const rank);
  void Render_live_data(int const score, int const lifes);

  void Clear_screen(void);
  void Update_screen(void);
             
  void UpdateWindowTitle(void);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *sdl_texture_name;
  SDL_Texture *sdl_texture_play;
  SDL_Texture *sdl_texture_play_again;
  SDL_Texture *sdl_texture_quit;
  SDL_Texture *sdl_texture_ptr;
  SDL_Texture *sdl_texture_msg;
  
  SDL_Texture *sdl_texture_spaceship;
  SDL_Texture *sdl_texture_player_fire;
  SDL_Texture *sdl_texture_score;
  SDL_Texture *sdl_texture_lifes;
  std::vector<SDL_Texture*> sdl_texture_aliens;
  std::vector<SDL_Texture*> sdl_texture_aliens_fires;

  std::mutex render_mtx;

  TTF_Font* font;
  SDL_Color textColor = { 250, 250, 250 };

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
