#include "Vector2.hpp"

// Static variables definitions
///////////////////////////////////////////////
inline const Vector2 Vector2::ZERO(0.0f, 0.0f);
inline const Vector2 Vector2::ONE(1.0f, 1.0f);
///////////////////////////////////////////////

///////////////////////////////////////////////
const Vector2& Vector2::operator=(const Vector2& other)
{
  this->x = other.x;
  this->y = other.y;
  
  return *this;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
bool Vector2::operator==(const Vector2& other)
{
  return (this->x == other.x) && (this->y == other.y);
}

bool Vector2::operator!=(const Vector2& other)
{
  return (this->x != other.x) || (this->y != other.y);
}
// -------------------------------------------
///////////////////////////////////////////////

///////////////////////////////////////////////
Vector2 Vector2::operator*(const Vector2& other)
{
  return Vector2(this->x * other.x, this->y * other.y);
}

Vector2 Vector2::operator*(const float f)
{
  return Vector2(this->x * f, this->y * f);
}

Vector2& Vector2::operator*=(Vector2 other)
{
  this->x *= other.x;
  this->y *= other.y;

  return *this;
}

Vector2& Vector2::operator*=(float f)
{
  this->x *= f;
  this->y *= f; 

  return *this;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
Vector2 Vector2::operator+(const Vector2& other)
{
  return Vector2(this->x + other.x, this->y + other.y); 
}

Vector2 Vector2::operator+(float f)
{
  return Vector2(this->x + f, this->y + f); 
}

Vector2& Vector2::operator+=(Vector2 other)
{
  this->x = this->x + other.x;
  this->y = this->y + other.y;

  return *this;
}

Vector2& Vector2::operator+=(float f)
{ 
  this->x = this->x + f;
  this->y = this->y + f;

  return *this;
}
///////////////////////////////////////////////

///////////////////////////////////////////////
Vector2 Vector2::operator-(const Vector2& other)
{
  return Vector2(this->x - other.x, this->y - other.y); 
}

Vector2 Vector2::operator-(float f)
{
  return Vector2(this->x - f, this->y - f); 
}

Vector2& Vector2::operator-=(Vector2 other)
{
  this->x = this->x - other.x;
  this->y = this->y - other.y;

  return *this;
}

Vector2& Vector2::operator-=(float f)
{ 
  this->x = this->x - f;
  this->y = this->y - f;

  return *this;
}
///////////////////////////////////////////////
