#pragma once

#include "../Enums/Anchor.hpp"
#include "Button.hpp"

#include <raylib.h>

#include <string>
#include <memory>

namespace ooh {
 
class ItemFrame 
{
  public:
    ItemFrame(Texture2D texture, Anchor anc, const std::string&& title, int itemCost, Vector2 offset = Vector2{0.0f, 0.0f});
    ~ItemFrame();

  public:
    Texture2D texture;
    Anchor anchor;
    std::string title, desc;
    int fontSize, cost;
    Vector2 position, origin, outlineSize, descLength, titleLength;
    Color outlineColor, descColor, textColor;
    Rectangle outlineRec, descRec;
    std::unique_ptr<Button> button;  

  public:
    void Render();
    void Reset();
    void SetDesc(const std::string&& description);

  private:
    bool m_isDescShown;
};

}
