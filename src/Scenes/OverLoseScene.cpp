#include "OverLoseScene.hpp"
#include "../Enums/SceneType.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../UI/Text.hpp"
#include "../UI/Button.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <cstdint>
#include <string>

namespace ooh {

OverLoseScene::OverLoseScene()
{
  title = Text("YOU WERE OUT ONLY HOPE...", Anchor::TOP_CENTER, TextType::BIG);
  waveText = Text("YOU SURVIVED: " + std::to_string(wave) + " WAVES", Anchor::CENTER, TextType::MEDIUM);
  menuButton = Button("MENU", Anchor::CENTER, TextType::MEDIUM, Vector2{0.0f, 60.0f});
}

OverLoseScene::~OverLoseScene()
{}

void OverLoseScene::Update(float dt)
{
  if(menuButton.OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
}

void OverLoseScene::Render()
{
  title.Render();
  waveText.Render();
  menuButton.Render();
}
void OverLoseScene::Reset()
{
  EventManager::Get().DispatchEvent<OnMusicStop>("Combat_Hymn");
  EventManager::Get().DispatchEvent<OnMusicPlay>("Over_Hymn");

  wave = util::GetDataFromFile<uint32_t>(global::WV_DAT_FILE_NAME);
  waveText.ChangeText("YOU SURVIVED " + std::to_string(wave) + " WAVES");
}
  
}
