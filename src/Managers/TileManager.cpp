#include "TileManager.hpp"
#include "../Entities/Tile.hpp"
#include "AssetManager.hpp"
#include "../Utils/Util.hpp"
#include "../Enums/BodyType.hpp"

#include <raylib.h>

#include <vector>
#include <memory>
#include <string>

namespace ooh {

TileManager::TileManager(const std::string&& img)
{
  m_srcImg = LoadImageFromTexture(AssetManager::Get().GetSprite(img));

  for(int y = 0; y < m_srcImg.height; y++)
  {
    for(int x = 0; x < m_srcImg.width; x++)
    {
      // Get the color of the pixel at the specified position in the image 
      Color pixelColor = GetImageColor(m_srcImg, x, y);
      std::string tileID;  

      // BLACK = Walls
      if(util::IsColorEqual(pixelColor, BLACK))
        tileID = "Wall_Tile";
      // WHITE = Grass
      else if(util::IsColorEqual(pixelColor, WHITE))
        tileID = "Grass_Tile";

      m_tiles.push_back(std::make_shared<Tile>(tileID, Vector2{x * TILE_SIZE / 1.0f, y * TILE_SIZE / 1.0f}, BodyType::STATIC));
    }
  }
}

TileManager::~TileManager()
{
  m_tiles.clear();
}

void TileManager::Render()
{
  for(auto& tile : m_tiles)
  {
    tile->Render();
  }
}

}
