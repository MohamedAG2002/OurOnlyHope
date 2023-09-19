#pragma once 

#include "../Enums/SceneType.hpp"

#include <functional>
#include <string>

namespace ooh {

using OnEntityCollision = std::function<void(std::string&, std::string&)>;
using OnSceneChange = std::function<void(SceneType)>;
using OnSoundPlay = std::function<void(std::string&&)>;
using OnMusicPlay = std::function<void(std::string&&)>;
using OnMusicStop = std::function<void(std::string&)>;
using OnQuit = std::function<void(void)>;

}
