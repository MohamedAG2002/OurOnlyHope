#include "AssetManager.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

AssetManager& AssetManager::Get()
{
  static AssetManager instance;
  return instance;
}

void AssetManager::LoadAssets(SDL_Renderer* renderer)
{
  LoadFont();
  LoadSprites(renderer);
  LoadSounds();
  LoadMusic();
}

void AssetManager::LoadFont()
{
  auto load = [&](const std::string& font, const std::string& path, int size) {
     m_fonts[font] = TTF_OpenFont(path.c_str(), size); 
  };
  
  load("Letter", "assets/font/bit5x3.ttf", 12);
  load("Small", "assets/font/bit5x3.ttf", 24);
  load("Medium", "assets/font/bit5x3.ttf", 36);
  load("Big", "assets/font/bit5x3.ttf", 48);

  // Err if any of the fonts do not load
  // Only checking for the first font because they all have the same path
  if(!m_fonts["Small"])
    std::cout << TTF_GetError() << std::endl;
}

void AssetManager::LoadSprites(SDL_Renderer* renderer)
{
  auto load = [&](const std::string& sprite, const std::string& path) {
     m_sprites[sprite] = IMG_LoadTexture(renderer, path.c_str()); 
  };

  // Adding sprites

  // Checking for errors
  for(auto[key, value] : m_sprites)
  {
    if(!value)
      std::cout << IMG_GetError() << std::endl;
  }
}

void AssetManager::LoadSounds()
{
  auto load = [&](const std::string& sound, const std::string& path) {
     m_sounds[sound] = Mix_LoadWAV(path.c_str()); 
  };

  // Adding sounds
  load("Button_Click", "assets/audio/button_click.wav");

  // Checking for errors
  for(auto[key, value] : m_sounds)
  {
    if(!value)
      std::cout << Mix_GetError() << std::endl;
  }
}

void AssetManager::LoadMusic()
{
  auto load = [&](const std::string& music, const std::string& path) {
     m_music[music] = Mix_LoadMUS(path.c_str()); 
  };

  // Adding music
  load("Menu_Hymn", "assets/audio/menu_hymn.ogg");
  
  // Checking for errors
  for(auto[key, value] : m_music)
  {
    if(!value)
      std::cout << Mix_GetError() << std::endl;
  }
}

void AssetManager::UnloadAssets()
{
  UnloadFont();
  UnloadSprites();
  UnloadSounds();
  UnloadMusic();
}

void AssetManager::UnloadFont()
{
  for(auto[key, value] : m_fonts)
    TTF_CloseFont(value);

  m_fonts.clear();
}

void AssetManager::UnloadSprites()
{
  for(auto[key, value] : m_sprites)
    SDL_DestroyTexture(value);
  
  m_sprites.clear();
}

void AssetManager::UnloadSounds()
{
  for(auto[key, value] : m_sounds)
    Mix_FreeChunk(value);
  
  m_sounds.clear();
}

void AssetManager::UnloadMusic()
{
  for(auto[key, value] : m_music)
    Mix_FreeMusic(value);
  
  m_music.clear();
}

TTF_Font* AssetManager::GetFont(const std::string&& fontName)
{
  return m_fonts[fontName];
}

SDL_Texture* AssetManager::GetSprite(const std::string& spriteName)
{
  return m_sprites[spriteName];
}

Mix_Chunk* AssetManager::GetSound(const std::string& soundName)
{
  return m_sounds[soundName];
}

Mix_Music* AssetManager::GetMusic(const std::string& musicName)
{
  return m_music[musicName];
}
