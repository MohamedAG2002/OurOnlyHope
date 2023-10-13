#pragma once

#include "../Enums/BodyType.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/WeaponType.hpp"
#include "../Enums/ArmorType.hpp"
#include "../Enums/PotionType.hpp"
#include "../Metadata/ShopItemsMetadata.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

#include <cstdint>
#include <random>
#include <fstream>
#include <iostream>

namespace ooh {
 
namespace util {

float ClampF(float value, float min, float max);
int ClampI(int value, int min, int max);
float GetRandomFloat(float min, float max);
float GetAngle(Vector2 point1, Vector2 point2);
bool IsColorEqual(Color c1, Color c2);

// Converts the first range given (min1 and max1) to the second range given (min2 and max2).
// The returned value will be a value between the first range given in the "format" of the 
// second range, while still maintaing the ratio.
float ConvertRange(float value, float min1, float max1, float min2, float max2);

// Will check if the given "desired" is equal to either "type1" or "type2"
bool CheckEntityType(std::string& type1, std::string& type2, std::string&& desired);

// Return a specific position based on the given Anchor
Vector2 SetPositionByAnchor(Anchor anc, Vector2 size, Vector2 offset);

// These functions will open and read a yaml file, extracing all of the information 
// inside and returning the metadata to the you so that you can use it. Just specify 
// the specific node that you need to deserialize and it will return the appropriate 
// metadata with the correct information.
WeaponMetadata LoadWeaponMetadata(const std::string& node);
ArmorMetadata LoadArmorMetadata(const std::string& node);
PotionMetadata LoadPotionMetadata(const std::string& node);

template<typename T>
T GetRandomNumber()
{
  std::random_device rndDevice;
  std::default_random_engine rndEngine(rndDevice());
  std::uniform_int_distribution<T> uniformDist;

  return uniformDist(rndEngine);
}

// Saves the given data to a file with the given file name at the 
// specified position. The "position" param is going to be a single bit number. 
// It's purpose is going to be to know where exactly in the file to begin 
// saving.
template<typename T>
void SaveDataToFile(const std::string&& fileName, T data)
{
  // Open the file in write mode
  std::fstream file(fileName, std::ios::out | std::ios::binary);

  // Err if the file did not open
  if(!file.is_open())
  {
    return;
    std::cerr << "File: " << fileName << " failed to open" << std::endl;
  }
  
  // Save the data to the file as a binary stream
  file.write((char*)&data, sizeof(data));
  
  // ALWAYS REMEMBER TO CLOSE THE FILE
  file.close();
}

// Starts to write at the given position to the 
// specified file using the given file name.
template<typename T>
T GetDataFromFile(const std::string&& fileName)
{
  // Open the file in read mode
  std::fstream file(fileName, std::ios::in | std::ios::binary);
  T data = 0;

  // Err if the file did not open
  if(!file.is_open())
  {
    return 0;
    std::cerr << "File: " << fileName << " failed to open" << std::endl;
  }

  // Read the contents of the file at the position 
  // specified to the buffer(the data variable that will be returned).
  file.read((char*)&data, sizeof(data));
  
  // ALWAYS REMEMBER TO CLOSE THE FILE
  file.close();

  return data;
}

// Box2D utilties
Vector2 B2Vec2ToVector2(b2Vec2 vec);
b2Vec2 Vector2ToB2Vec2(Vector2 vec);
b2BodyType BodyTypeToB2BodyType(BodyType type);
BodyType B2BodyTypeToBodyType(b2BodyType type);

}

}
