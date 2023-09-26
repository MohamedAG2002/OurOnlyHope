#pragma once 

#include "../Enums/SceneType.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <functional>
#include <string>

namespace ooh {

using OnEntityCollision = std::function<void(BodyMetadata& bodyMD1, BodyMetadata& bodyMD2)>;
using OnSceneChange = std::function<void(SceneType)>;
using OnSoundPlay = std::function<void(std::string&&)>;
using OnMusicPlay = std::function<void(std::string&&)>;
using OnMusicStop = std::function<void(std::string&)>;
using OnQuit = std::function<void(void)>;

}
