#include <iostream> 

#include "game.h"
#include "renderer.h"


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{16};
  constexpr std::size_t kGridHeight{16};

  int aliens_forces = 40;
  bool state = true;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, aliens_forces);
  
  while(state){
    Game game(&renderer, kScreenWidth, kScreenHeight, aliens_forces);
    if(game.start(kMsPerFrame)){
      if(game.Run(kMsPerFrame)) { state = game.end(kMsPerFrame); }
      else { state = false; }
    }
    else { state = false; }
  }

  std::cout << "Game has terminated successfully!\n";
  // std::cout << "Score: " << game.get_score() << "\n";
  return 0;
}
