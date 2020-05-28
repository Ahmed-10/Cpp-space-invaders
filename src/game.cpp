#include "game.h"
#include <iostream>
#include <algorithm>

Game::Game(std::size_t screen_width, std::size_t screen_height, int aliens_forces)
    : _screen_width(screen_width) , _screen_height(screen_height)
    , _is_player_fire(false) , _aliens_forces(aliens_forces)
{
  Spaceship player(screen_height, screen_width);
  _player = player;

  int x = screen_width / 8;
  int y = screen_height / 10;

  for(size_t i = 1; i <= aliens_forces; i++){
    _aliens.emplace_back(Alien(x, y));
  
    x += 40;  
    if(i % 10 == 0){
    	x = screen_width / 8;
    	y += 56;	
    }
  }
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

    renderer.Render_spirit(_player.get_x_pos(), _player.get_y_pos());

    for(size_t i = 0; i < _aliens_forces; i++)
      renderer.Render_aliens(_aliens[i].get_x_pos(), _aliens[i].get_y_pos(), _aliens[i].get_rank());

    //update aliens position

    if(_aliens.front().get_x_pos() <= 0){
      _direction = Direction::kRight;
      for(size_t i = 0; i < _aliens_forces; i++){
        _aliens[i].update_position(Direction::kDown);
        _aliens[i].update_position(Direction::kRight);
      }  
    }
    else if (_aliens[_aliens_forces - 1].get_x_pos() >= (_screen_width - 40))
    {
      _direction = Direction::kLeft;
      for(size_t i = 0; i < _aliens_forces; i++){
        _aliens[i].update_position(Direction::kDown);
        _aliens[i].update_position(Direction::kLeft);
      } 
    }
    else
    {
      for(size_t i = 0; i < _aliens_forces; i++){
        _aliens[i].update_position(_direction);
      } 
    }
    
    

    if(_is_player_fire){
    
      for(size_t i = 0; i < _player_fire.size(); i++){

        renderer.Render_spirit_fire(_player_fire[i].get_x_pos(), _player_fire[i].get_y_pos());
        
        _player_fire[i].update_position();

        for(size_t j = 0; j < _aliens_forces; j++){
          int x_ = _aliens[j].get_x_pos();
          int y_ = _aliens[j].get_y_pos();

          if((_player_fire[i].get_x_pos() >= (x_ - 16)) && (_player_fire[i].get_x_pos() <= (x_ + 16))
          && (_player_fire[i].get_y_pos() >= (y_ - 16)) && (_player_fire[i].get_y_pos() <= (y_ + 16)))
          {
            _aliens.erase(_aliens.begin() + j);
            _player_fire.erase(_player_fire.begin());
            _aliens_forces --;
          }  
        }
        
        if(_player_fire[i].get_y_pos() == 0){ _player_fire.erase(_player_fire.begin()); }
      }
        if(_player_fire.size() == 0) { _is_player_fire = false; }
    }



    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution<int> random_1(0, 3);
    std::uniform_int_distribution<int> random_2(0, static_cast<int>(_aliens.size() - 1));

    int fire_level = random_1(engine);
    
    if(_alien_fire.size() < fire_level){
      for(size_t i = 0; i < 3; i++){
        int rand = random_2(engine);
        std::cout << rand << std::endl;
        _alien_fire.emplace_back(Fire(_aliens[rand].get_x_pos()
                                    , _aliens[rand].get_y_pos()
                                    , _aliens[rand].get_rank()));
      }
    }
    
    for(size_t i = 0; i < _alien_fire.size(); i++){

      renderer.Render_aliens_fire(_alien_fire[i].get_x_pos()
                                , _alien_fire[i].get_y_pos()
                                , _alien_fire[i].get_rank());
      
      _alien_fire[i].update_position();
  
      if(_alien_fire[i].get_y_pos() >= _screen_height){
        _alien_fire.erase(_alien_fire.begin() + i);
        i--;
      }
    }

    renderer.Update_screen();

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
            _player.update_position(Direction::kRight);
            break;
          case SDLK_LEFT:
            _player.update_position(Direction::kLeft);
            break;
          case SDLK_SPACE:
            _player_fire.push_back(Fire(_player.get_x_pos(), _player.get_y_pos()));
            _is_player_fire = true;
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

