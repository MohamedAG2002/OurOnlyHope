#pragma once

#include "../Components/Transform2D.hpp"

namespace ooh {

class Entity 
{
  public:
    Transform2D transform;
    int UUID;
    bool isActive;

  public:
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};

}
