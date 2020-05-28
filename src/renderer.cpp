#include "renderer.h"
#include "iostream"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, 
                   const std::size_t grid_height,
                   int aliens_forces)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
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
  //spirit texture
  SDL_Surface* surface = IMG_Load("../gfx/spirit.png");
  sdl_texture_spaceship = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);
  
  //spirit fire texture
  surface = IMG_Load("../gfx/shoot0.png");
  sdl_texture_player_fire = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  //alien random texture
  std::random_device dev;
  std::mt19937 engine(dev());
  std::uniform_int_distribution<int> random(0, static_cast<int>(_aliens_imgs.size()-1));

  for(size_t i = 0; i < _aliens_imgs.size(); i++){
    int img = random(engine);

    surface = IMG_Load(_aliens_imgs[img].c_str());
    sdl_texture_aliens.emplace_back(SDL_CreateTextureFromSurface(sdl_renderer, surface));
    SDL_FreeSurface(surface);

    surface = IMG_Load(_aliens_fire_imgs[img].c_str());
    sdl_texture_aliens_fires.emplace_back(SDL_CreateTextureFromSurface(sdl_renderer, surface));
    SDL_FreeSurface(surface);
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyTexture(sdl_texture_spaceship);
  SDL_DestroyTexture(sdl_texture_player_fire);
  
  int size = sdl_texture_aliens.size();
  for(size_t i = 0; i < size; i++){
    SDL_DestroyTexture(sdl_texture_aliens[i]);
    SDL_DestroyTexture(sdl_texture_aliens_fires[i]);
  }

  IMG_Quit();
  SDL_Quit();
}

void Renderer::Render_spirit(int const x, int const y) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render Entity
  block.x = x;
  block.y = y - (grid_width * 3);
  SDL_RenderCopy(sdl_renderer, sdl_texture_spaceship, nullptr, &block);
}

  // Render aliens
void Renderer::Render_aliens(int const x, int const y, int const rank){
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  block.x = x;
  block.y = y;
      
  SDL_RenderCopy(sdl_renderer, sdl_texture_aliens[rank], nullptr, &block);
}

// Render Entity shoot
void Renderer::Render_spirit_fire(int const x, int const y) {
  SDL_Rect block;
  block.w = 4;
  block.h = 8;
  block.x = x;
  block.y = y;
  SDL_RenderCopy(sdl_renderer, sdl_texture_player_fire, nullptr, &block); 
}

// Render Aliens fire
void Renderer::Render_aliens_fire(int x, int y, int rank) {
  SDL_Rect block;
  block.w = 8;
  block.h = 16;
  block.x = x;
  block.y = y;
  SDL_RenderCopy(sdl_renderer, sdl_texture_aliens_fires[rank], nullptr, &block); 
}

void Renderer::UpdateWindowTitle() {
  std::string title{"space invaders"};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::Clear_screen(void){
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
}

void Renderer::Update_screen(void){
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}