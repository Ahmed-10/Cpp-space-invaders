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

  if (TTF_Init() == -1){
    std::cerr << "SDL ttf could not initialize.\n";
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
  //text texture
  font = TTF_OpenFont("../gfx/courier-new.ttf", 56);
  SDL_Surface* surface = TTF_RenderText_Solid(font, "s p a c e  i n v a d e r s", textColor);
  sdl_texture_name = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  surface = TTF_RenderText_Solid(font, "play", textColor);
  sdl_texture_play = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  surface = TTF_RenderText_Solid(font, "play again", textColor);
  sdl_texture_play_again = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  surface = TTF_RenderText_Solid(font, "quit", textColor);
  sdl_texture_quit = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  surface = IMG_Load("../gfx/pointer1.png");
  sdl_texture_ptr = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  //spirit texture
  surface = IMG_Load("../gfx/spirit.png");
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
  SDL_DestroyTexture(sdl_texture_name);
  SDL_DestroyTexture(sdl_texture_play);
  SDL_DestroyTexture(sdl_texture_play_again);
  SDL_DestroyTexture(sdl_texture_quit);
  SDL_DestroyTexture(sdl_texture_ptr);
  SDL_DestroyTexture(sdl_texture_msg);
  SDL_DestroyTexture(sdl_texture_spaceship);
  SDL_DestroyTexture(sdl_texture_player_fire);
  SDL_DestroyTexture(sdl_texture_score);
  SDL_DestroyTexture(sdl_texture_lifes);
  
  int size = sdl_texture_aliens.size();
  for(size_t i = 0; i < size; i++){
    SDL_DestroyTexture(sdl_texture_aliens[i]);
    SDL_DestroyTexture(sdl_texture_aliens_fires[i]);
  }

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Renderer::Render_game_name(){
  SDL_Rect block;
  block.w = 400;
  block.h = 60;
  block.x = 100;
  block.y = 100;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_name, nullptr, &block);
}

void Renderer::Render_play_opt(){
  SDL_Rect block;
  block.w = 40;
  block.h = 20;
  
  block.x = 400;
  block.y = 200;
  SDL_RenderCopy(sdl_renderer, sdl_texture_ptr, nullptr, &block);
  
  block.w = 100;
  block.h = 20;
  block.x = 450;
  block.y = 200;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_play, nullptr, &block);

  block.x = 450;
  block.y = 250;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_quit, nullptr, &block);

  SDL_Surface* surface = TTF_RenderText_Solid(font, "push Enter to start playing", textColor);
  sdl_texture_msg = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  block.w = 400;
  block.h = 20;
  
  block.x = 100;
  block.y = 400;
  SDL_RenderCopy(sdl_renderer, sdl_texture_msg, nullptr, &block);
}

void Renderer::Render_quit_opt(){
  SDL_Rect block;
  block.w = 40;
  block.h = 20;
  
  block.x = 400;
  block.y = 250;
  SDL_RenderCopy(sdl_renderer, sdl_texture_ptr, nullptr, &block);
  
  block.w = 100;
  block.h = 20;
  block.x = 450;
  block.y = 200;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_play, nullptr, &block);

  block.x = 450;
  block.y = 250;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_quit, nullptr, &block);

  SDL_Surface* surface = TTF_RenderText_Solid(font, "push Enter to quit the game", textColor);
  sdl_texture_msg = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  block.w = 400;
  block.h = 20;
  
  block.x = 100;
  block.y = 400;
  SDL_RenderCopy(sdl_renderer, sdl_texture_msg, nullptr, &block);
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

void Renderer::Render_live_data(int const score, int const lifes){
  std::string score_("score: " + std::to_string(score));
  std::string lifes_("lifes: " + std::to_string(lifes));
  
  SDL_Surface* surface = TTF_RenderText_Solid(font, score_.c_str(), textColor);
  sdl_texture_score = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  surface = TTF_RenderText_Solid(font, lifes_.c_str(), textColor);
  sdl_texture_lifes = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  SDL_Rect block;
  block.w = 100;
  block.h = 20;
  block.x = 10;
  block.y = 10;
  SDL_RenderCopy(sdl_renderer, sdl_texture_score, nullptr, &block);

  block.x = 10;
  block.y = 40;
  SDL_RenderCopy(sdl_renderer, sdl_texture_lifes, nullptr, &block);
}

void Renderer::Render_play_again(int score){
  SDL_Rect block;
  block.w = 40;
  block.h = 20;
  
  block.x = 150;
  block.y = 400;
  SDL_RenderCopy(sdl_renderer, sdl_texture_ptr, nullptr, &block);
  
  block.w = 200;
  block.h = 20;
  block.x = 200;
  block.y = 400;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_play_again, nullptr, &block);
  
  block.w = 100;
  block.x = 250;
  block.y = 450;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_quit, nullptr, &block);

  SDL_Surface* surface;
  if(score < 40){
    surface = TTF_RenderText_Solid(font, "Game Over!", textColor);
  }
  else
  {
    surface = TTF_RenderText_Solid(font, "You win!", textColor);
  }
  
  sdl_texture_msg = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  std::string score_("score: " + std::to_string(score));
  surface = TTF_RenderText_Solid(font, score_.c_str(), textColor);
  sdl_texture_score = SDL_CreateTextureFromSurface(sdl_renderer, surface);

  block.w = 200;
  block.h = 20;
  
  block.x = 200;
  block.y = 200;
  SDL_RenderCopy(sdl_renderer, sdl_texture_msg, nullptr, &block);

  block.w = 100;
  block.h = 20;
  
  block.x = 250;
  block.y = 250;
  SDL_RenderCopy(sdl_renderer, sdl_texture_score, nullptr, &block);
}

void Renderer::Render_exit(int score){
  SDL_Rect block;
  block.w = 40;
  block.h = 20;
  
  block.x = 150;
  block.y = 450;
  SDL_RenderCopy(sdl_renderer, sdl_texture_ptr, nullptr, &block);
  
  block.w = 200;
  block.h = 20;
  block.x = 200;
  block.y = 400;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_play_again, nullptr, &block);
  
  block.w = 100;
  block.x = 250;
  block.y = 450;
  // Render Entity
  SDL_RenderCopy(sdl_renderer, sdl_texture_quit, nullptr, &block);

  SDL_Surface* surface;
  if(score < 40){
    surface = TTF_RenderText_Solid(font, "Game Over!", textColor);
  }
  else
  {
    surface = TTF_RenderText_Solid(font, "You win!", textColor);
  }
  
  sdl_texture_msg = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  std::string score_("score: " + std::to_string(score));
  surface = TTF_RenderText_Solid(font, score_.c_str(), textColor);
  sdl_texture_score = SDL_CreateTextureFromSurface(sdl_renderer, surface);

  block.w = 200;
  block.h = 20;
  
  block.x = 200;
  block.y = 200;
  SDL_RenderCopy(sdl_renderer, sdl_texture_msg, nullptr, &block);

  block.w = 100;
  block.h = 20;
  
  block.x = 250;
  block.y = 250;
  SDL_RenderCopy(sdl_renderer, sdl_texture_score, nullptr, &block);
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