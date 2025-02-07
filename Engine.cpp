#include "Engine.h"
#include "LevelManager.h"
#include "TimerManager.h"

using namespace Input;

Engine::Engine()
{
    window.create(VideoMode({ 800, 600 }), "Engine Window");
    inputManager = InputManager();
    backgroundColor = Color::Blue;
}                
                                                                                                                                                              

void Engine::Start()
{
    Update();
    Stop();
};

void Engine::Update()
{
    while (window.isOpen())
    {
        TM_Seconds& _timer = M_TIMER;
        _timer.Update();

        Level* _currentLevel = M_LEVEL.GetCurrentLevel();
        if (_currentLevel)
        {
            const float _deltaTime = _timer.GetDeltaTime().asSeconds();
            _currentLevel->Update(_deltaTime);
            continue;
        }
    }
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
    window.clear(backgroundColor);
    window.display();
}

void Engine::Stop()
{
    M_LEVEL.Destroy();
}