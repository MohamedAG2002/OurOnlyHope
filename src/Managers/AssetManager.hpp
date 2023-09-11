#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <unordered_map>

// A singleton class to handle all of the assets in the game
class AssetManager
{
  // Methods
  ////////////////////////////////////////////// 
  public:
    // Call this everytime a method or member of this class needs to be accessed
    static AssetManager& Get();

    // Loads all of the assets
    void LoadAssets(SDL_Renderer* renderer); 

    // Loads only the font
    void LoadFont();

    // Loads only the sprites
    void LoadSprites(SDL_Renderer* renderer);

    // Loads only the sounds
    void LoadSounds();

    // Loads only the music 
    void LoadMusic();
  
    // Unload all of the assets
    void UnloadAssets();
    
    // Unload only the font
    void UnloadFont();
    
    // Unload only the sprites
    void UnloadSprites();
    
    // Unload only the sounds
    void UnloadSounds();

    // Unloads only the music 
    void UnloadMusic();

    // Return the font
    TTF_Font* GetFont(const std::string&& fontName);

    // Return the sprite
    SDL_Texture* GetSprite(const std::string& spriteName);

    // Return the sound
    Mix_Chunk* GetSound(const std::string& soundName); 
    
    // Return the music
    Mix_Music* GetMusic(const std::string& musicName); 
  ////////////////////////////////////////////// 

  // Funky stuff to make this class a singleton
  ////////////////////////////////////////////// 
  public:
    // Deleting the copy constructor 
    AssetManager(const AssetManager&) = delete;

    // Making it impossible to assign this class
    void operator=(const AssetManager&) = delete;
  ////////////////////////////////////////////// 

  // Members   
  ////////////////////////////////////////////// 
  private:
    std::unordered_map<std::string, TTF_Font*> m_fonts;      
    std::unordered_map<std::string, SDL_Texture*> m_sprites;      
    std::unordered_map<std::string, Mix_Chunk*> m_sounds;      
    std::unordered_map<std::string, Mix_Music*> m_music;      
  ////////////////////////////////////////////// 

  // Private CTOR
  ////////////////////////////////////////////// 
  private:
    AssetManager() {}
    ~AssetManager() {}
  ////////////////////////////////////////////// 
};
