#include "Engine.h"
#include "LevelManager.h"
#include "TimerManager.h"

Engine::Engine()
{
    inputManager = Input::InputManager();
}                
                                                                                                                                                              

void Engine::Start()
{
    Update();
    Stop();
};

void Engine::Update()
{
    while (Level* _currentLevel = M_LEVEL.GetCurrentLevel())
    {
        TM_Seconds& _timer = M_TIMER;
        const float _deltaTime = _timer.Update();
        _currentLevel->Update(_deltaTime);
    }
}

void Engine::Stop()
{
    M_LEVEL.Destroy();
}