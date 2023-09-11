#include "Managers/GameManager.hpp"

int main(int argc, char** argv)
{
  GameManager* game = new GameManager();
  game->Run();
  delete game;

  return 0;
}
