#pragma once

#include <raylib.h>

class Scene 
{
  public:
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Reset() = 0;
};
