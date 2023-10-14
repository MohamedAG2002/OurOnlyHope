#pragma once 

#include "../Enums/SceneType.hpp"
#include "../Enums/PotionType.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <raylib.h>

#include <functional>
#include <string>

namespace ooh {

// Gameplay events 
using OnBloodInc = std::function<void(int)>; 
using OnWaveEnd = std::function<void(void)>;
using OnItemEquip = std::function<void(const std::string&)>;

// Engine events 
using OnEntityCollision = std::function<void(BodyMetadata& bodyMD1, BodyMetadata& bodyMD2)>;
using OnSceneChange = std::function<void(SceneType)>;
using OnParticleSpawn = std::function<void(const Vector2)>;
using OnSoundPlay = std::function<void(std::string&&)>;
using OnMusicPlay = std::function<void(const std::string&&)>;
using OnMusicStop = std::function<void(std::string&&)>;

// System events 
using OnQuit = std::function<void(bool)>;
using OnPause = std::function<void(void)>;

}
