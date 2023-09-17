#pragma once

#include "../Components/Transform2D.hpp"

#include <iostream>

namespace ooh {

class Entity 
{
  public:
    Transform2D transform;
    std::string id;
    bool isActive;

  public:
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};

}
