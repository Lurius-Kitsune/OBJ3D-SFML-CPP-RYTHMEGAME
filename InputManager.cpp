#include "InputManager.h"

Input::InputManager::InputManager()
{
    actionsMaps = map<string, ActionMap*>();
    keysIsHolding = set<Key>();
    mouseButtonsIsHolding = set<Button>();
    joysticksButtonsIsHolding = vector<set<int>>();
    for (int _joystickId = 0; _joystickId < Joystick::Count; _joystickId++)
    {
        joysticksButtonsIsHolding.push_back(set<int>());
    }
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
    using Iterator = map<string, ActionMap*>::iterator;
    for (Iterator _iterator = actionsMaps.begin(); _iterator != actionsMaps.end(); )
    {
        ActionMap* _actionMap = _iterator->second;
        _actionMap->Update(_event);
        if (_actionMap->IsToDelete())
        {
            --_iterator;
            RemoveActionMap(_actionMap->GetName());
            continue;
        }

        ++_iterator;
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
        if (_event->is<PressedKey>())
        {
            for (int _keyIndex = 0; _keyIndex < Keyboard::KeyCount; _keyIndex++)
            {
                const Key& _key = CAST(Key, _keyIndex);
                if (Keyboard::isKeyPressed(_key) && !keysIsHolding.contains(_key))
                {
                    keysIsHolding.insert(_key);
                }
            }
        }
        else if (_event->is<ReleasedKey>())
        {
            for (int _keyIndex = 0; _keyIndex < Keyboard::KeyCount; _keyIndex++)
            {
                const Key& _key = CAST(Key, _keyIndex);
                if (!Keyboard::isKeyPressed(_key) && keysIsHolding.contains(_key))
                {
                    keysIsHolding.erase(_key);
                }
            }
        }
        else if (_event->is<PressedMouseButton>())
        {
            for (int _keyIndex = 0; _keyIndex < Mouse::ButtonCount; _keyIndex++)
            {
                const Button& _mouseButton = CAST(Button, _keyIndex);
                if (Mouse::isButtonPressed(_mouseButton) && !mouseButtonsIsHolding.contains(_mouseButton))
                {
                    mouseButtonsIsHolding.insert(_mouseButton);
                }
            }
        }
        else if (_event->is<ReleasedMouseButton>())
        {
            for (int _keyIndex = 0; _keyIndex < Mouse::ButtonCount; _keyIndex++)
            {
                const Button& _mouseButton = CAST(Button, _keyIndex);
                if (!Mouse::isButtonPressed(_mouseButton) && mouseButtonsIsHolding.contains(_mouseButton))
                {
                    mouseButtonsIsHolding.erase(_mouseButton);
                }
            }
        }
        else if (_event->is<ControllerJoystickPressed>())
        {
            for (int _joystickId = 0; _joystickId < Joystick::Count; _joystickId++)
            {
                if (!Joystick::isConnected(_joystickId)) continue;
                for (int _keyIndex = 0; _keyIndex < Joystick::ButtonCount; _keyIndex++)
                {
                    if (Joystick::isButtonPressed(_joystickId, _keyIndex) &&
                        !joysticksButtonsIsHolding[_joystickId].contains(_keyIndex))
                    {
                        joysticksButtonsIsHolding[_joystickId].insert(_keyIndex);
                    }
                }
            }
        }
        else if (_event->is<ControllerJoystickReleased>())
        {
            for (int _joystickId = 0; _joystickId < Joystick::Count; _joystickId++)
            {
                if (!Joystick::isConnected(_joystickId)) continue;
                for (int _keyIndex = 0; _keyIndex < Joystick::ButtonCount; _keyIndex++)
                {
                    if (!Joystick::isButtonPressed(_joystickId, _keyIndex) &&
                        joysticksButtonsIsHolding[_joystickId].contains(_keyIndex))
                    {
                        joysticksButtonsIsHolding[_joystickId].erase(_keyIndex);
                    }
                }
            }
        }
    }
}