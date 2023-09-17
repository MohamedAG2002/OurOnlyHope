#pragma once

#include <raylib.h>

namespace ooh {

class Transform2D 
{
  public:
    // This CTOR should be used and prioritized over the default one
    Transform2D(Vector2 pos, float rotation = 0.0f, Vector2 scale = Vector2{1.0f, 1.0f})
      :position(pos), rotation(rotation), scale(scale)
    {}

    // Default CTOR
    Transform2D() 
      :position(Vector2{0.0f, 0.0f}), rotation(0.0f), scale(Vector2{0.0f, 0.0f})
    {}
    
    // Destructor
    ~Transform2D()
    {}

  public:
    Vector2 position, scale;
    float rotation;

  public:
    // Moves the position of the transform by the given velocity and applies the delta time
    void Move(Vector2 velocity);

    // Rotate the transform by the given offset taking into account the previous values
    void Rotate(float rotation);

    // Scales the transform by the given factor taking into account the previous values.
    // NOTE: The scale on both the X and Y axis starts at 1
    void Scale(Vector2 factor); 
};

}
