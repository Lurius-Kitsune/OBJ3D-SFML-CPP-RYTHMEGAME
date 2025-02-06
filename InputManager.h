#pragma once
#include "Singleton.h"
#include "ActionMap.h"

namespace Input
{

	class InputManager : public Singleton<InputManager>
	{
		map<string, ActionMap*> actionsMaps;
		bool isKeyHolding;
		bool isButtonHolding;

	private:
		FORCEINLINE void AddActionMap(const pair<string, ActionMap*>& _actionMap)
		{
			actionsMaps.insert(_actionMap);
		}
	public:
		FORCEINLINE bool GetIsKeyHolding() const
		{
			return isKeyHolding;
		}
		FORCEINLINE bool GetIsButtonHolding() const
		{
			return isButtonHolding;
		}
		FORCEINLINE ActionMap* GetActionMapByName(const string& _name)
		{
			if (!actionsMaps.contains(_name)) return nullptr;
			return actionsMaps.at(_name);
		}
		FORCEINLINE void RemoveActionMap(const string& _name)
		{
			if (!actionsMaps.contains(_name)) return;

			delete actionsMaps[_name];
			actionsMaps.erase(_name);
		}
		FORCEINLINE ActionMap* CreateActionMap(const string& _name)
		{
			if (actionsMaps.contains(_name))
			{
				LOG(Error, "This ActionMap's name (" + _name + ") already used !");
				return nullptr;
			}

			ActionMap* _actionMap = new ActionMap(_name);
			AddActionMap({ _name, _actionMap });
			return _actionMap;
		}

	public:
		InputManager();
		~InputManager();

	private:
		void UpdateActionMaps(const EventInfo& _event);

	public:
		void Update(RenderWindow& _window);
	};
}

#pragma region Exemple
/*
ActionMap* _actionMap = M_INPUT.CreateActionMap("Demo");
//DIGITAL
_actionMap->AddAction("Test", ActionData(MouseEntered), [&]() { LOG(Error, "ButtonEntered"); });
_actionMap->AddAction("Test1", ActionData(KeyPressed, Key::A), [&]() { LOG(Display, "coucou"); });
_actionMap->AddAction("Test2", ActionData(KeyReleased, Key::A), [&]() { LOG(Warning, "coucou"); });
_actionMap->AddAction("Test3", ActionData(KeyHold, Key::A), [&]() { LOG(Error, "coucou"); });
_actionMap->AddAction("Test4", ActionData(KeyPressed, Key::B), [&]() { LOG(Display, "salut"); });
_actionMap->AddAction("Test5", ActionData(KeyReleased, Key::B), [&]() { LOG(Warning, "salut"); });
_actionMap->AddAction("Test6", ActionData(KeyHold, Key::B), [&]() { LOG(Error, "salut"); });
_actionMap->AddAction("Test9", ActionData(KeyHold, Key::T), [&]() { LOG(Error, "Thomas"); });
_actionMap->AddAction("Test8", ActionData(KeyReleased, Key::T), [&]() { LOG(Warning, "Thomas"); });
_actionMap->AddAction("Test7", ActionData(KeyPressed, Key::T), [&]() { LOG(Display, "Thomas"); });
//AXIS2
_actionMap->AddAction("Test10", ActionData(MouseMoved), [&](const Vector2f& _position) { LOG(Error, "X: " + to_string(_position.x) + " Y: " + to_string(_position.y)); });
_actionMap->AddAction("Test11", ActionData(MouseMovedRaw), [&](const Vector2f& _position) { LOG(Error, "MouseMovedRaw"); });
//AXIS
_actionMap->AddAction("Test12", ActionData(MouseWheelScrolled, Mouse::Wheel::Vertical), [&](const float _position) { LOG(Error, to_string(_position)); });

_actionMap->Enable();
*/
#pragma endregion
