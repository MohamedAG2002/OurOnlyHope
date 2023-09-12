#include "Entity.hpp"
#include "../Components/Transform.hpp"

#include <cstdio>
#include <iostream>

void Entity::ToString()
{
  std::cout << id << ": {Pos: (" << transform.position.x << ", " << transform.position.y << "), Active: " << isActive << "}\n";
}
