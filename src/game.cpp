#include "game.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <future>

Game::Game(Renderer* renderer, std::size_t screen_width, std::size_t screen_height, int aliens_forces)
    : _screen_width(screen_width) , _screen_height(screen_height)
    , _aliens_forces(aliens_forces), _renderer(renderer)
{
  //create spaceship
  _player = std::make_unique<Spaceship> (screen_height, screen_width);

  //postion the tp left of the alien formation
  int x = screen_width / 8;
  int y = screen_height / 10;
  //create aliens
  for(size_t i = 1; i <= aliens_forces; i++){
    _aliens.emplace_back(std::make_unique<Alien> (x, y));
  
    x += 40;  
    if(i % 10 == 0){
    	x = screen_width / 8;
    	y += 56;	
    }
  }

  _running = true;
}

void Game::draw_spaceship(){
  std::lock_guard<std::mutex> lock(_player_mtx);
  _renderer->Render_spirit(_player->get_x_pos(), _player->get_y_pos());
}

void Game::draw_aliens(){
  std::lock_guard<std::mutex> lock(_aliens_mtx);
  size_t size = _aliens.size();
  for(size_t i = 0; i < size; i++)
    _renderer->Render_aliens(_aliens[i]->get_x_pos()
                            , _aliens[i]->get_y_pos()
                            , _aliens[i]->get_rank());
}

void Game::draw_spaceship_fire(){
  size_t size = _player_fire.size();
  for(size_t i = 0; i < size; i++)
    _renderer->Render_spirit_fire(_player_fire[i]->get_x_pos()
                                , _player_fire[i]->get_y_pos());
}

void Game::draw_aliens_fire(){
  size_t size = _aliens_fire.size();
  for(size_t i = 0; i < size; i++)
    _renderer->Render_aliens_fire(_aliens_fire[i]->get_x_pos()
                                , _aliens_fire[i]->get_y_pos()
                                , _aliens_fire[i]->get_rank());
}

void Game::update_spaceship(){
  std::lock_guard<std::mutex> lock(_player_mtx);
  if(go_right){
    _player->update_position(Direction::kRight);
    go_right--;
  }
  if(go_left){
    _player->update_position(Direction::kLeft);
    go_left--;
  }
}

void Game::update_aliens(){
  std::lock_guard<std::mutex> lock(_aliens_mtx);
  size_t size = _aliens.size();

  int min_x = _screen_width, max_x = 0, max_y = 0;
  for(size_t i = 0; i < size; i++){
    if(_aliens[i]->get_x_pos() < min_x) { min_x = _aliens[i]->get_x_pos(); }
    if(_aliens[i]->get_x_pos() > max_x) { max_x = _aliens[i]->get_x_pos(); }
    if(_aliens[i]->get_y_pos() > max_y) { max_y = _aliens[i]->get_y_pos(); }
  }

  if (max_y >= _screen_height - 60)
  {
    _running = false;
  }  

  if (min_x <= 0)
  {
    for (size_t i = 0; i < size; i++)
    {
      _aliens[i]->update_position(Direction::kDown);
      _aliens[i]->update_position(Direction::kRight);
      _direction = Direction::kRight;
    }    
  }
  else if (max_x >= _screen_width - 40)
  {
    for (size_t i = 0; i < size; i++)
    {
      _aliens[i]->update_position(Direction::kDown);
      _aliens[i]->update_position(Direction::kLeft);
      _direction = Direction::kLeft;
    }
  }
  else
  {
    for (size_t i = 0; i < size; i++)
    {
      _aliens[i]->update_position(_direction);
    }
  }  
}

void Game::update_spaceship_fire(){
  
  for (size_t i = 0; i < _player_fire.size(); i++){
    _player_fire[i]->update_position();

    //if the fire element went out of the screen
    if (_player_fire[i]->get_y_pos() < 0)
    {
      _player_fire.erase(_player_fire.begin() + i);
      i--;
    }
    else
    {

      size_t size = _aliens.size();
      int x_ = _player_fire[i]->get_x_pos();
      int y_ = _player_fire[i]->get_y_pos();
      for (size_t j = 0; j < size; j++)
      {
        std::unique_lock<std::mutex> lock(_aliens_mtx);
        int x = _aliens[j]->get_x_pos();
        int y = _aliens[j]->get_y_pos();
        lock.unlock();
        //check collision with the aliens
        if((x_ > x) && (x_ < (x + 40)) && (y_ > y) && (y_ < (y + 40))){
          _score++;
          lock.lock();
          _aliens.erase(_aliens.begin() + j);
          if (_aliens.size() == 0) { _running = false; }
          lock.unlock();
          j--;
          _player_fire.erase(_player_fire.begin() + i);
          i--;
          break;
        }
      }
      
    }
    
  }  
}

void Game::update_aliens_fire(){
  std::unique_lock<std::mutex> lock(_aliens_mtx);
  if(_aliens.size() > 0){
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution<int> rand_level(0, 3);
    std::uniform_int_distribution<int> rand_pos(0, static_cast<int>(_aliens.size() - 1));

    int fire_density = rand_level(engine);
    fire_density = fire_density - _aliens_fire.size();
    
    while (fire_density > 0)
    {
      fire_density --;
      int fire_pos = rand_pos(engine);
      _aliens_fire.emplace_back(std::make_unique<Fire>(_aliens[fire_pos]->get_x_pos()
                                                    , _aliens[fire_pos]->get_y_pos()
                                                    , _aliens[fire_pos]->get_rank()));
    }
  }  
  lock.unlock();
  
  std::unique_lock<std::mutex> lck(_player_mtx);
  int x = _player->get_x_pos();
  int y = _player->get_y_pos();
  lck.unlock();

  for (size_t i = 0; i < _aliens_fire.size(); i++)
  {
    _aliens_fire[i]->update_position();

    int x_ = _aliens_fire[i]->get_x_pos();
    int y_ = _aliens_fire[i]->get_y_pos();

    //if the fire element went out of the screen
    if (_aliens_fire[i]->get_y_pos() > _screen_height)
    {
      _aliens_fire.erase(_aliens_fire.begin() + i);
      i--;
    }
    //check collision with the spaceship
    else if ((x_ > x) && (x_ < (x + 40)) && (y_ + 16 >= y))
    {
      _lifes --;
      if (_lifes == 0) { _running = false; }
      _aliens_fire.erase(_aliens_fire.begin() + i);
      i--;
    }
    
  }
}

void Game::event_handle(){
  SDL_Event Events;
  while (SDL_PollEvent(&Events))
  {
    switch (Events.type)
    {
    case SDL_QUIT:
      _running = false;
      _return = false;
      break;
    case SDL_KEYDOWN:
      if(Events.key.keysym.sym == SDLK_LEFT){
        go_left++;
      }

      if(Events.key.keysym.sym == SDLK_RIGHT){
        go_right++;
      }

      if(Events.key.keysym.sym == SDLK_SPACE){
        std::unique_lock<std::mutex> lock(_player_mtx);
        _player_fire.emplace_back(std::make_unique<Fire>(_player->get_x_pos() + 20, _player->get_y_pos() - 20));
        lock.unlock();
      }
      break;
    default:
      break;
    }   
  }  
}

bool Game::Run(std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0; 

  while (_running) {

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //note: should create a variable with the number of killed aliens could be score
    //and the alien fire should increase and apend new member to the vector 
    _renderer->Clear_screen();

    // std::thread t0(&Game::event_handle, this);
    std::future<void> ftr0 = std::async(&Game::event_handle, this);
    // std::thread t1(&Game::draw_spaceship, this);
    std::future<void> ftr1 = std::async(&Game::draw_spaceship, this);
    // std::thread t3(&Game::draw_aliens, this);
    std::future<void> ftr3 = std::async(&Game::draw_aliens, this);
    // std::thread t5(&Game::draw_spaceship_fire, this);
    std::future<void> ftr5 = std::async(&Game::draw_spaceship_fire, this);
    // std::thread t7(&Game::draw_aliens_fire, this);
    std::future<void> ftr7 = std::async(&Game::draw_aliens_fire, this);
    
    ftr3.get();//t3.join();
    // std::thread t4(&Game::update_aliens, this);
    std::future<void> ftr4 = std::async(&Game::update_aliens, this);
    ftr0.get();//t0.join();
    ftr1.get();//t1.join();
    // std::thread t2(&Game::update_spaceship, this);
    std::future<void> ftr2 = std::async(&Game::update_spaceship, this); 
    ftr5.get();//t5.join();
    // std::thread t6(&Game::update_spaceship_fire, this);
    std::future<void> ftr6 = std::async(&Game::update_spaceship_fire, this);
    ftr7.get();//t7.join();
    // std::thread t8(&Game::update_aliens_fire, this);
    std::future<void> ftr8 = std::async(&Game::update_aliens_fire, this);
    
    _renderer->Render_live_data(get_score(), get_lifes());

    _renderer->Update_screen();

    frame_end = SDL_GetTicks();

    // // Keep track of how long each loop through the input/update/render cycle
    // // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer->UpdateWindowTitle();
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
    SDL_Delay(target_frame_duration - frame_duration);
    }

    // t2.join();
    // t4.join();
    // t6.join();
    // t8.join();
    ftr2.get();
    ftr4.get();
    ftr6.get();
    ftr8.get();
  }

  _running = true;
  return _return;
}

bool Game::start(std::size_t target_frame_duration){
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  SDL_Event Events;

  while(_running){ 
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //note: should create a variable with the number of killed aliens could be score
    //and the alien fire should increase and apend new member to the vector 
    _renderer->Clear_screen();
    
    //render game name
    _renderer->Render_game_name();

    if (_return) { _renderer->Render_play_opt(); }
    else { _renderer->Render_quit_opt(); }


    _renderer->Update_screen();

    frame_end = SDL_GetTicks();

    // // Keep track of how long each loop through the input/update/render cycle
    // // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
        _renderer->UpdateWindowTitle();
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
        _running = false;
        _return = false;
        break;
      case SDL_KEYDOWN:
        switch(Events.key.keysym.sym)
        {
        case SDLK_UP:
          if(_return == true) { _return = false; }
          else { _return = true; }
          break;
        case SDLK_DOWN:
          if(_return == true) { _return = false; }
          else { _return = true; }
          break;
        case SDLK_KP_ENTER:
          _running = false;
          break;
        default: break;
        } break;
      default: break;
      }   
    }
  }

  _running = true;
  return _return;
}

bool Game::end(std::size_t target_frame_duration){
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  SDL_Event Events;

  while(_running){ 
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //note: should create a variable with the number of killed aliens could be score
    //and the alien fire should increase and apend new member to the vector 
    _renderer->Clear_screen();
    
    //render game name
    _renderer->Render_game_name();

    if (_return) { _renderer->Render_play_again(_score); }
    else { _renderer->Render_exit(_score); }


    _renderer->Update_screen();

    frame_end = SDL_GetTicks();

    // // Keep track of how long each loop through the input/update/render cycle
    // // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
        _renderer->UpdateWindowTitle();
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
        _running = false;
        _return = false;
        break;
      case SDL_KEYDOWN:
        switch(Events.key.keysym.sym)
        {
        case SDLK_UP:
          if(_return == true) { _return = false; }
          else { _return = true; }
          break;
        case SDLK_DOWN:
          if(_return == true) { _return = false; }
          else { _return = true; }
          break;
        case SDLK_KP_ENTER:
          _running = false;
          break;
        default: break;
        } break;
      default: break;
      }   
    }
  }

  _running = true;

  return _return;
}

int Game::get_score() { 
  return _score; 
}

int Game::get_lifes() { 
  return _lifes; 
}
