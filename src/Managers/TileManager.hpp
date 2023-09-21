#pragma once

#include "../Entities/Tile.hpp"

#include <raylib.h>

#include <vector>
#include <memory>
#include <string>

namespace ooh {

class TileManager 
{
  public:
    TileManager(const std::string&& img);
    ~TileManager();

  public:
    void Render();

  private:
    Texture2D m_tileMap;
    std::vector<std::unique_ptr<Tile>> m_tiles;
};
  
}
