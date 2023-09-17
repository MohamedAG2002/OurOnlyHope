#include "Managers/GameManager.hpp"

int main()
{
  ooh::GameManager* game = new ooh::GameManager();
  game->Run();
  delete game;
}
