#include "Engine.h"
#include "TimerManager.h"
#include "LevelManager.h"

using namespace Input;
using namespace Camera;


Engine::Engine()
{
    window.create(VideoMode({600,600}), "Engine Window");
}                
                                                                                                                                                              

void Engine::Start()
{
   // ActionMap* _actionMap = M_INPUT.CreateActionMap("Demo");
    Update();
    Stop();
};

void Engine::Update()
{
    while (window.isOpen())
    {
        TM_Seconds& _timer = M_TIMER;
        _timer.Update();
        const float _deltaTime = _timer.GetDeltaTime().asSeconds();
        Level* _currentLevel = M_LEVEL.GetCurrentLevel();
        if(_currentLevel)
        {
            _currentLevel->Tick(_deltaTime);
            continue;
        }
        
    }
}

void Engine::Stop()
{
    M_LEVEL.Destroy();
}

void Engine::UpdateWindow()
{
    Level* _currentLevel = M_LEVEL.GetCurrentLevel();
    window.setVisible(!_currentLevel);
    if (_currentLevel)
    {
        _currentLevel->UpdateWindow();
        return;
    }
    inputManager.Update(window);
    window.clear(Color::Blue);
    window.display();

    if (!window.isOpen())
    {
        Stop();
    }

}

