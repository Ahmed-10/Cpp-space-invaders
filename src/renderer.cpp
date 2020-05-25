#include "renderer.h"
#include <iostream>
#include <string>
#include <random>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, 
                   const std::size_t grid_height,
                   int aliens_forces)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      _aliens_forces(aliens_forces)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::cerr << "SDL image could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("space invaders", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  } 

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_Surface* surface = IMG_Load("../gfx/spirit.png");
  sdl_texture_spaceship = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  std::random_device dev;
  std::mt19937 engine(dev());
  std::uniform_int_distribution<int> random(0, static_cast<int>(_aliens_imgs.size()-1));

  for(size_t i = 0; i < aliens_forces; i++){
    int img = random(engine);
    surface = IMG_Load(_aliens_imgs[img].c_str());
    sdl_texture_aliens.emplace_back(SDL_CreateTextureFromSurface(sdl_renderer, surface));
    SDL_FreeSurface(surface);
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyTexture(sdl_texture_spaceship);
  
  for(int num = 0; num < _aliens_forces; num++){
    SDL_DestroyTexture(sdl_texture_aliens[num]);
  }
  IMG_Quit();
  SDL_Quit();
}

void Renderer::Render(Spaceship const spirit, Alien const aliens) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render Entity
  block.x = spirit.pos_x;
  block.y = spirit.pos_y - (grid_width * 3);
  SDL_RenderCopy(sdl_renderer, sdl_texture_spaceship, nullptr, &block);

  // Render Entity shoot
  

  // Render aliens

  for(size_t i = 0; i < _aliens_forces; i++){
    block.x = aliens._matrix_pos[i].first;
    block.y = aliens._matrix_pos[i].second;
    SDL_RenderCopy(sdl_renderer, sdl_texture_aliens[i], nullptr, &block);
  }
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle() {
  std::string title{"space invaders"};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
