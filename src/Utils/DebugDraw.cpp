#include "DebugDraw.hpp"
#include "Util.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

namespace ooh {

DebugDraw::DebugDraw()
{
  uint8 flags = 0;
  flags += e_aabbBit;
  SetFlags(flags);
}

DebugDraw::~DebugDraw()
{}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
  Vector2 points[vertexCount + 1];
  for(int i = 0; i < vertexCount + 1; i++)
  { 
    // The index should wrap around when at the end to create a full rectangle  
    // around the body
    points[i] = util::B2Vec2ToVector2(vertices[(i % vertexCount)]);
  }

  DrawLineStrip(points, vertexCount + 1, WHITE);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}
  
}
