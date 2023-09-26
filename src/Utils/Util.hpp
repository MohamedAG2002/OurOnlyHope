#pragma once

#include "../Enums/BodyType.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

#include <cstdint>
#include <random>
#include <fstream>
#include <iostream>

namespace ooh {
 
namespace util {

// OOH utilites 
float ClampF(float value, float min, float max);
int ClampI(int value, int min, int max);
float GetAngle(Vector2 point1, Vector2 point2);
bool IsColorEqual(Color c1, Color c2);

// Will check if the given "desired" is equal to either "type1" or "type2"
bool CheckEntityType(std::string& type1, std::string& type2, std::string&& desired);

template<typename T>
T GetRandomNumber()
{
  std::random_device rndDevice;
  std::default_random_engine rndEngine(rndDevice());
  std::uniform_int_distribution<T> uniformDist;

  return uniformDist(rndEngine);
}

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

template<typename T>
T GetDataFromFile(const std::string&& fileName)
{
  // Open the file in read mode
  std::fstream file(fileName, std::ios::in | std::ios::binary);
  T data;

  // Err if the file did not open
  if(!file.is_open())
  {
    return 0;
    std::cerr << "File: " << fileName << " failed to open" << std::endl;
  }

  // Enter into read mode
  file.read((char*)&data, sizeof(data));

  // Read the file from left to right/top to bottom
  while(!file.eof())
  {
    // Read the contents of the file into the variable
    file.read((char*)&data, sizeof(data)); 
  }
  
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
