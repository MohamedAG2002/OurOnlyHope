#pragma once

#include "../Entities/Tile.hpp"

#include <raylib.h>

#include <vector>
#include <memory>

namespace ooh {

class TileManager 
{
  public:
    TileManager();
    ~TileManager();

  public:
    void Render();

  private:
    std::vector<std::unique_ptr<Tile>> m_tiles;
};
  
}
