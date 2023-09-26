#pragma once

#include "../Events/EventFuncs.hpp"

#include <vector>
#include <utility>
#include <algorithm>
#include <type_traits>

namespace ooh {

// A singleton class to handle the dispatch and listening to events
class EventManager 
{
  public:
    static EventManager& Get();
    void UnloadEvents();

    // Template functions to dispatch and listen to specific events
    ///////////////////////////////////////////////////////////////
    // Push back the function pointer given to the appropriate events vector
    template<typename T>
    void ListenToEvent(T&& func)
    {
      // Checking--at compile time--which type the given template is and passing the 
      // function pointer to the appropriate vector.
      if constexpr (std::is_same<T, OnEntityCollision>::value)
        m_collisionEvents.push_back(static_cast<OnEntityCollision>(func));
      else if constexpr (std::is_same<T, OnBloodInc>::value)
        m_bloodEvents.push_back(static_cast<OnBloodInc>(func));
      else if constexpr (std::is_same<T, OnWaveEnd>::value)
        m_waveEvents.push_back(static_cast<OnWaveEnd>(func));
      else if constexpr (std::is_same<T, OnSceneChange>::value)
        m_sceneEvents.push_back(static_cast<OnSceneChange>(func));
      else if constexpr (std::is_same<T, OnSoundPlay>::value)
        m_soundEvents.push_back(static_cast<OnSoundPlay>(func));
      else if constexpr (std::is_same<T, OnMusicPlay>::value)
        m_musicPlayEvents.push_back(static_cast<OnMusicPlay>(func));
      else if constexpr (std::is_same<T, OnMusicStop>::value)
        m_musicStopEvents.push_back(static_cast<OnMusicStop>(func));
      else if constexpr (std::is_same<T, OnQuit>::value)
        m_quitEvents.push_back(static_cast<OnQuit>(func));
    }
   
    // Dispatch/Call the specified event with the given arguments
    template<typename T, typename... Args>
    void DispatchEvent(Args&&... args)
    {
      // Making a lambda function that will be passed into the for_each
      // function below. All this lambda does is check if the passed in 
      // function pointer is valid and calls it if it is.
      auto callFn = [&](const T& fn) {
        if(fn)
          fn(std::forward<Args>(args)...);
      };

      // Checking the exact template type and calling the appropriate function 
      // pointer, giving it the given arguments.
      if constexpr (std::is_same<T, OnEntityCollision>::value)
        std::for_each(m_collisionEvents.begin(), m_collisionEvents.end(), callFn);
      else if constexpr (std::is_same<T, OnBloodInc>::value)
        std::for_each(m_bloodEvents.begin(), m_bloodEvents.end(), callFn);
      else if constexpr (std::is_same<T, OnWaveEnd>::value)
        std::for_each(m_waveEvents.begin(), m_waveEvents.end(), callFn);
      else if constexpr (std::is_same<T, OnSceneChange>::value)
        std::for_each(m_sceneEvents.begin(), m_sceneEvents.end(), callFn);
      else if constexpr (std::is_same<T, OnSoundPlay>::value)
        std::for_each(m_soundEvents.begin(), m_soundEvents.end(), callFn);
      else if constexpr (std::is_same<T, OnMusicPlay>::value)
        std::for_each(m_musicPlayEvents.begin(), m_musicPlayEvents.end(), callFn);
      else if constexpr (std::is_same<T, OnMusicStop>::value)
        std::for_each(m_musicStopEvents.begin(), m_musicStopEvents.end(), callFn);
      else if constexpr (std::is_same<T, OnQuit>::value)
        std::for_each(m_quitEvents.begin(), m_quitEvents.end(), callFn);
    }
    ///////////////////////////////////////////////////////////////

    // Deleting the copy constructor
    EventManager(const EventManager&) = delete;
    
    // Making the class unassaignable
    void operator=(const EventManager&) = delete;

  private:
    std::vector<OnEntityCollision> m_collisionEvents;
    std::vector<OnBloodInc> m_bloodEvents;
    std::vector<OnWaveEnd> m_waveEvents;
    
    std::vector<OnSceneChange> m_sceneEvents;
    std::vector<OnSoundPlay> m_soundEvents;
    std::vector<OnMusicPlay> m_musicPlayEvents;
    std::vector<OnMusicStop> m_musicStopEvents;
    std::vector<OnQuit> m_quitEvents;

  private:
    EventManager() {}
    ~EventManager() {}
};
  
}
