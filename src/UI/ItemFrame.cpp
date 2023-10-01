#include "ItemFrame.hpp"
#include "../Enums/Anchor.hpp"
#include "../Utils/Util.hpp"

#include <raylib.h>

namespace ooh {
 

ItemFrame::ItemFrame(Texture2D texture, Anchor anc, const std::string&& title, Vector2 offset)
  :texture(texture), anchor(anc), title(title)
{
  desc = "DAM = 30\nDUR = 100\nRAN = 40\nLBS = 20";

  fontSize = 15;

  outlineSize = Vector2{32.0f, 32.0f};
  origin = Vector2{outlineSize.x / 2.0f, outlineSize.y / 2.0f};
  position = util::SetPositionByAnchor(anchor, outlineSize, offset); 
  descLength = MeasureTextEx(GetFontDefault(), desc.c_str(), fontSize, 1.0f); 
  titleLength = MeasureTextEx(GetFontDefault(), title.c_str(), fontSize, 1.0f); 

  outlineColor = GREEN;
  descColor = BROWN;
  textColor = WHITE;
  
  outlineRec = Rectangle{position.x - origin.x, position.y - origin.y, outlineSize.x, outlineSize.y};
  descRec = Rectangle{position.x, position.y, descLength.x + 20, 100.0f};

  m_isDescShown = false;
}

ItemFrame::~ItemFrame()
{}

void ItemFrame::Render()
{
  // Check if the mouse is hovering over the item frame
  if(CheckCollisionPointRec(GetMousePosition(), outlineRec))
    m_isDescShown = true;
  else 
    m_isDescShown = false;

  // Drawing the outline 
  DrawRectangleLinesEx(outlineRec, 1.0f, outlineColor);

  // Drawing the item's texture 
  DrawTextureV(texture, Vector2{position.x - origin.x, position.y - origin.y}, WHITE);

  // Drawing the title of the item frame 
  DrawText(title.c_str(), position.x - titleLength.x / 2.0f, position.y + 25.0f, fontSize, textColor);

  // Only drawing the description box and text when the mouse is hovering 
  // over the item frame.
  if(!m_isDescShown)
    return;
  
  DrawRectangleRec(descRec, Color{BROWN.r, BROWN.g, BROWN.b, 210});
  DrawText(desc.c_str(), descRec.x + 10.0f, descRec.y + 10.0f, fontSize, textColor);
}

}
