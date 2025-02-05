#pragma once
#include "CoreMinimal.h"

namespace Input
{
	typedef optional<Event> EventInfo;
	using ActionType = type_index;
	using Key = Keyboard::Key;

	using KeyPressed = Event::KeyPressed;
	using KeyReleased = Event::KeyReleased;
	using MouseButtonPressed = Event::MouseButtonPressed;
	using MouseButtonReleased = Event::MouseButtonReleased;

	enum ControllerButtonsType
	{
		Start,
		Select,
		Cross,
		Circle,
		Triangle,
		Square,
		L1,
		R1,
		L2,
		R2,
		LeftStick,
		RightStick
	};

	enum ControllerAxesType
	{
		LeftStickX,
		LeftStickY,
		RightStickX,
		RightStickY,
	};


	enum ValueType
	{
		Digital, // bool
		Axis,	 // float
		Axis2,	 // Vector2f
	};

	struct ActionData
	{
		ValueType value;
		ActionType type = typeid(Event::KeyPressed);
		int key;

		template <typename Type>
		ActionData(const ActionType& _type, int _key)
		{
			value = Digital;
			type = typeid(Type);
			key = _key;
		}
	};

	class Action
	{
		string name;
		multimap<ActionType, ActionData> allData;
		function<void()> callback;

	public:
		FORCEINLINE string GetName() const
		{
			return name;
		}
		template <typename Type>
		FORCEINLINE void SetTrigger()
		{
			data.trigger = typeid(Type);
		}

	public:
		Action(const string& _name, const ActionData& _data, const function<void()>& _callback);
		Action(const string& _name, const set<ActionData>& _allData, const function<void()>& _callback);

		void TryToExecute(const EventInfo& _event);
	};
}