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
    Image m_srcImg;
    std::vector<std::shared_ptr<Tile>> m_tiles;
};
  
}
