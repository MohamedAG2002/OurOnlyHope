#include "DebugDraw.hpp"
#include "Vector2.hpp"
#include "Utils.hpp"

#include <SDL2/SDL.h>
#include <box2d/box2d.h>

DebugDraw::DebugDraw(SDL_Renderer* renderer)
  :m_renderer(renderer)
{
  uint8 flags = 0;
  flags += e_aabbBit;
  SetFlags(flags);
}

DebugDraw::~DebugDraw()
{}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
  SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

  SDL_FPoint points[vertexCount];
  for(int i = 0; i < vertexCount; i++)
  {
    Vector2 pixelVec = B2Vec2ToVector2(vertices[i]);
    points[i] = SDL_FPoint{pixelVec.x, pixelVec.y};
  }

  SDL_RenderDrawLinesF(m_renderer, points, vertexCount);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
  //SDL_Log("SOLID Polygon");
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
  //SDL_Log("Circle");
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
  //SDL_Log("SOLID Cirlce");
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
  //SDL_Log("Segment");
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
  //SDL_Log("SOLID Transform");
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
  //SDL_Log("Point");
}

