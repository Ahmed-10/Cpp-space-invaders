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

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, aliens_forces);
  Game game(kScreenWidth, kScreenHeight, aliens_forces);
  game.Run(renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " <<"\n";
  std::cout << "Size: " << "\n";
  return 0;
}
