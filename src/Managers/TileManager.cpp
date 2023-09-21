#include "TileManager.hpp"
#include "../Entities/Tile.hpp"
#include "AssetManager.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Enums/BodyType.hpp"

#include <raylib.h>

#include <vector>
#include <memory>
#include <string>

namespace ooh {

TileManager::TileManager(const std::string&& img)
{
  m_tileMap = AssetManager::Get().GetSprite(img);

  // Util variables
  Vector2 screenSize = Vector2{(float)GetScreenWidth(), (float)GetScreenHeight()};
 
  // Walls init
  // This perhaps looks like a mess but it's not. The tiles are only containers for the body and collider and what 
  // is happening below is me setting the positions of the bodies explicitly. This might look bad to you but it is 
  // way more effecient than using something like LDtk or Tiled and importing a whole parser into the project. Setting 
  // the bodies by hand might look bad but it is better than importing another sdk into the project.
  m_tiles.emplace_back(std::make_unique<Tile>("West_Wall", Vector2{TILE_SIZE / 2.0f, TILE_SIZE * 8.5f}, Vector2{TILE_SIZE, screenSize.y * 2.5f}));
  m_tiles.emplace_back(std::make_unique<Tile>("East_Wall", Vector2{screenSize.x - TILE_SIZE / 2.0f, TILE_SIZE * 8.5f}, Vector2{TILE_SIZE, screenSize.y * 2.5f}));
  m_tiles.emplace_back(std::make_unique<Tile>("North_Wall", Vector2{TILE_SIZE * 10, TILE_SIZE / 2.0f}, Vector2{screenSize.x * 2.5f, TILE_SIZE}));
  m_tiles.emplace_back(std::make_unique<Tile>("South_Wall", Vector2{TILE_SIZE * 10, screenSize.y - TILE_SIZE / 2.0f}, Vector2{screenSize.x * 2.5f, TILE_SIZE}));
}

TileManager::~TileManager()
{
  m_tiles.clear();
}

void TileManager::Render()
{
  DrawTexture(m_tileMap, 0, 0, WHITE);
}

}
