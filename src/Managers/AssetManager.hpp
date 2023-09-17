#pragma once

#include <raylib.h>

#include <string>
#include <unordered_map>

namespace ooh {

// A singleton class to handle all of the assets in the game
class AssetManager
{
  // Methods
  ////////////////////////////////////////////// 
  public:
    // Call this everytime a method or member of this class needs to be accessed
    static AssetManager& Get();

    // Loads all of the assets
    void LoadAssets(); 

    // Loads only the font
    void LoadFonts();

    // Loads only the sprites
    void LoadSprites();

    // Loads only the sounds
    void LoadSounds();

    // Loads only the music 
    void LoadMusic();
  
    // Unload all of the assets
    void UnloadAssets();
    
    // Unload only the font
    void UnloadFonts();
    
    // Unload only the sprites
    void UnloadSprites();
    
    // Unload only the sounds
    void UnloadSounds();

    // Unloads only the music 
    void UnloadMusic();

    // Return the font
    Font GetFont();

    // Return the sprite
    Texture2D GetSprite(const std::string& spriteName);

    // Return the sound
    Sound GetSound(const std::string& soundName); 
    
    // Return the music
    Music GetMusic(const std::string& musicName); 
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
    Font m_font;
    std::unordered_map<std::string, Texture2D> m_sprites;      
    std::unordered_map<std::string, Sound> m_sounds;      
    std::unordered_map<std::string, Music> m_music;      
  ////////////////////////////////////////////// 

  // Private CTOR
  ////////////////////////////////////////////// 
  private:
    AssetManager() {}
    ~AssetManager() {}
  ////////////////////////////////////////////// 
};

}
