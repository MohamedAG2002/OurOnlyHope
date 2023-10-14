cmake_minimum_required(VERSION 3.27.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For the LSP
set(CMAKE_BUILD_TYPE Debug) # Remember to turn this off in release builds

project(ooh VERSION 1.0)

# Directing cmake to where all the libraries are
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/libs/)

find_library(raylib raylib REQUIRED)
find_library(box2d box2d REQUIRED)
find_library(yaml-cpp yaml-cpp REQUIRED)

set(SOURCES
  # Base files
  src/main.cpp
  
  # Utils
  src/Utils/Util.cpp
  src/Utils/DebugDraw.cpp

  # Managers
  src/Managers/GameManager.cpp
  src/Managers/AssetManager.cpp
  src/Managers/EventManager.cpp
  src/Managers/SceneManager.cpp
  src/Managers/EntityManager.cpp
  src/Managers/ZombieManager.cpp
  src/Managers/TileManager.cpp
  src/Managers/WaveManager.cpp
  src/Managers/ParticleManager.cpp

  # Listeners
  src/Listeners/AudioListener.cpp
  src/Listeners/ContactListener.cpp
  
  # UI
  src/UI/Text.cpp
  src/UI/Button.cpp
  src/UI/Checkbox.cpp
  src/UI/ItemFrame.cpp

  # Scenes 
  src/Scenes/MenuScene.cpp
  src/Scenes/SettingScene.cpp
  src/Scenes/ShopScene.cpp
  src/Scenes/GameScene.cpp
  src/Scenes/OverWinScene.cpp
  src/Scenes/OverLoseScene.cpp
  src/Scenes/SecretScene.cpp

  # Components
  src/Components/Transform2D.cpp
  src/Components/Sprite.cpp
  src/Components/PhysicsBody.cpp
  src/Components/Collider.cpp
  src/Components/Animator.cpp

  # Entities
  src/Entities/Player.cpp
  src/Entities/Zombie.cpp
  src/Entities/Weapon.cpp
  src/Entities/Tile.cpp
  src/Entities/Particle.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Copying the assets and data folders to the binary
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Adding the include for the above libraries
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libs/include)

# Adding the libraries to the project
target_link_libraries(${PROJECT_NAME} 
  ${raylib}
  ${box2d}
  ${yaml-cpp}
)

# For windows builds
add_definitions(-DSDL_MAIN_HANDELED)
