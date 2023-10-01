#pragma once

#include "../Enums/Anchor.hpp"

#include <raylib.h>

#include <string>

namespace ooh {
 
class ItemFrame 
{
  public:
    ItemFrame(Texture2D texture, Anchor anc, const std::string&& title, Vector2 offset = Vector2{0.0f, 0.0f});
    ~ItemFrame();

  public:
    Texture2D texture;
    Anchor anchor;
    std::string title, desc;
    int fontSize;
    Vector2 position, origin, outlineSize, descLength, titleLength;
    Color outlineColor, descColor, textColor;
    Rectangle outlineRec, descRec;

  public:
    void Render();

  private:
    bool m_isDescShown;
};

}
