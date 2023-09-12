#pragma once

#include "../Utils/Vector2.hpp"

class Transform 
{
  public:
    // This CTOR should be used and prioritized over the default one
    Transform(Vector2 pos, Vector2 rotation = Vector2::ZERO, Vector2 scale = Vector2::ONE)
      :position(pos), rotation(rotation), scale(scale)
    {}

    // Default CTOR
    Transform() 
      :position(Vector2::ZERO), rotation(Vector2::ZERO), scale(Vector2::ONE)
    {}
    
    // Destructor
    ~Transform()
    {}

  public:
    Vector2 position, rotation, scale;

  public:
    // Moves the position of the transform by the given velocity and applies the delta time
    void Move(Vector2 velocity, float dt);

    // Rotate the transform by the given offset taking into account the previous values
    void Rotate(Vector2 offset);

    // Scales the transform by the given factor taking into account the previous values 
    // NOTE: The scale on both the X and Y axis starts at one
    void Scale(Vector2 factor); 
};
