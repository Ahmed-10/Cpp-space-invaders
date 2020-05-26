#include "game.h"
#include <iostream>
#include <algorithm>
#include "SDL2/SDL.h"
#include "spaceship.h"

Game::Game(std::size_t screen_width, std::size_t screen_height, int aliens_forces)
    : _spirit(screen_width, screen_height) 
    , _aliens(screen_width, screen_height, aliens_forces) 
{
  _screen_width = screen_width;
  _screen_height = _screen_height;
  _is_spirit_fire = false;
  _aliens_forces = aliens_forces;
}

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  
  SDL_Event Events;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //note: should create a variable with the number of killed aliens could be score
    //and the alien fire should increase and apend new member to the vector 
    renderer.Clear_screen();

    renderer.Render(_spirit, _aliens, _alien_fire);

    if(_is_spirit_fire){
    
      for(size_t i = 0; i < _player_fire.size(); i++){

        renderer.Render_spirit_fire(_player_fire[i].pos_x, _player_fire[i].pos_y);
        
        _player_fire[i].UpdatePosition();
        // std::cout << k++ << std::endl;
        for(int j = 0; j < _aliens_forces; j++){
          if(_aliens._matrix[j]){
            if((_player_fire[i].pos_x >= (_aliens._matrix_pos_x[j] - 16))
            && (_player_fire[i].pos_x <= (_aliens._matrix_pos_x[j] + 16))
            && (_player_fire[i].pos_y >= (_aliens._matrix_pos_y[j] - 16))
            && (_player_fire[i].pos_y <= (_aliens._matrix_pos_y[j] + 16)))
            {
              _aliens._matrix[j] = false;
              _player_fire.erase(_player_fire.begin());
            } 
          } 
        }
        
        if(_player_fire[i].pos_y == 0){ _player_fire.erase(_player_fire.begin());  k = 1; }
      }
        if(_player_fire.size() == 0) { _is_spirit_fire = false; }
    }

    renderer.Update_screen();

    _aliens.UpdatePosition();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle();
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    while (SDL_PollEvent(&Events))
    {
        switch (Events.type)
        {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          switch (Events.key.keysym.sym)
          {
          case SDLK_RIGHT:
            _spirit.UpdatePosition(Spaceship::Direction::kRight);
            break;
          case SDLK_LEFT:
            _spirit.UpdatePosition(Spaceship::Direction::kLeft);
            break;
          case SDLK_SPACE:
            _player_fire.push_back(Fire(_screen_width, _screen_height, _spirit));
            _is_spirit_fire = true;
            break;
          default:
            break;
          }
          break;
        default:
          break;
        }     
    }
  }
}

int Game::GetScore() const { return score; }

