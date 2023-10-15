#include "AssetManager.hpp"

#include <raylib.h>

#include <iostream>

namespace ooh {

AssetManager& AssetManager::Get()
{
  static AssetManager instance;
  return instance;
}

void AssetManager::LoadAssets()
{
  LoadFonts();
  LoadSprites();
  LoadSounds();
  LoadMusic();
}

void AssetManager::LoadFonts()
{
  m_font = LoadFont("assets/font/bit5x3.ttf");
}

void AssetManager::LoadSprites()
{
  auto load = [&](const std::string& sprite, const std::string& path) {
    m_sprites[sprite] = LoadTexture(path.c_str()); 
  };

  // Adding character sprites
  load("Player_Sprite", "assets/sprites/player.png");
  load("Zombie_Sprite", "assets/sprites/zombie.png");
  load("Spear", "assets/sprites/spear.png");
 
  // Adding potion sprites
  load("Health_Potion", "assets/sprites/potions/health_potion.png");
  load("Damage_Potion", "assets/sprites/potions/damage_potion.png");
  load("Defense_Potion", "assets/sprites/potions/defense_potion.png");
  load("Dexterity_Potion", "assets/sprites/potions/dexterity_potion.png");

  // Adding the map sprite 
  load("Map", "assets/sprites/map.png");
}

void AssetManager::LoadSounds()
{
  auto load = [&](const std::string& sound, const std::string& path) {
     m_sounds[sound] = LoadSound(path.c_str()); 
  };

  // Adding sounds
  load("Button_Click", "assets/audio/button_click.wav");
  
  load("Sword_Swing", "assets/audio/sword_swing.wav");
  load("Spear_Throw-1", "assets/audio/spear_throw-1.wav");
  load("Spear_Throw-2", "assets/audio/spear_throw-2.wav");
  
  load("Zombie_Death-1", "assets/audio/sword_kill_zombie-1.wav");
  load("Zombie_Death-2", "assets/audio/sword_kill_zombie-2.wav");
  load("Zombie_Grunt", "assets/audio/zombie_grunt.wav");

  load("Player_Death", "assets/audio/player_death.wav");
  load("Player_Hurt-1", "assets/audio/player_hurt-1.wav");
  load("Player_Hurt-2", "assets/audio/player_hurt-2.wav");
}

void AssetManager::LoadMusic()
{
  auto load = [&](const std::string& music, const std::string& path) {
     m_music[music] = LoadMusicStream(path.c_str()); 
  };

  // Adding music
  load("Menu_Hymn", "assets/audio/menu_hymn.ogg");
  load("Combat_Hymn", "assets/audio/combat_hymn.mp3");
  load("Over_Hymn", "assets/audio/over_hymn.ogg");
}

void AssetManager::UnloadAssets()
{
  UnloadFonts();
  UnloadSprites();
  UnloadSounds();
  UnloadMusic();
}

void AssetManager::UnloadFonts()
{
  UnloadFont(m_font);
}

void AssetManager::UnloadSprites()
{
  for(auto&[key, value] : m_sprites)
    UnloadTexture(value);
  
  m_sprites.clear();
}

void AssetManager::UnloadSounds()
{
  for(auto&[key, value] : m_sounds)
    UnloadSound(value);
  
  m_sounds.clear();
}

void AssetManager::UnloadMusic()
{
  for(auto&[key, value] : m_music)
    UnloadMusicStream(value);
  
  m_music.clear();
}

Font AssetManager::GetFont()
{
  return m_font;
}

Texture AssetManager::GetSprite(const std::string& spriteName)
{
  return m_sprites[spriteName];
}

Sound AssetManager::GetSound(const std::string& soundName)
{
  return m_sounds[soundName];
}

Music AssetManager::GetMusic(const std::string& musicName)
{
  return m_music[musicName];
}

}
