#include "InputManager.h"

Input::InputManager::InputManager()
{
    actionsMaps = map<string, ActionMap*>();
    isKeyHolding = false;
    isButtonHolding = false;
}

Input::InputManager::~InputManager()
{
    for (const pair<string, ActionMap*>& _pair : actionsMaps)
    {
        delete _pair.second;
    }
}


void Input::InputManager::UpdateActionMaps(const EventInfo& _event)
{
    for (const pair<string, ActionMap*>& _map : actionsMaps)
    {
        _map.second->Update(_event);
    }
}

void Input::InputManager::Update(RenderWindow& _window)
{
    while (const EventInfo& _event = _window.pollEvent())
    {
        if (_event->is<Event::Closed>())
        {
            _window.close();
            return;
        }

        UpdateActionMaps(_event);
        if (_event->is<PressedKey>() && !isKeyHolding)
        {
            isKeyHolding = true;
        }
        else if (_event->is<ReleasedKey>() && isKeyHolding)
        {
            isKeyHolding = false;
        }
        else if (_event->is<PressedMouseButton>() && !isButtonHolding)
        {
            isButtonHolding = true;
        }
        else if (_event->is<ReleasedMouseButton>() && isButtonHolding)
        {
            isButtonHolding = false;
        }
        else if (_event->is<PressedMouseButton>() && !isButtonHolding)
        {
            isJoystickButtonHolding = true;
        }
        else if (_event->is<ReleasedMouseButton>() && isButtonHolding)
        {
            isJoystickButtonHolding = false;
        }
    }
}