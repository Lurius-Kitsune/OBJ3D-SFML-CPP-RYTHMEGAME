#pragma once
#include "CoreMinimal.h"

namespace Input
{
#pragma region Typedef & Using
	typedef optional<Event> EventInfo;
	using TypeIndex = type_index;
	using Key = Keyboard::Key;

	//Keyboard
	using PressedKey = Event::KeyPressed;
	using ReleasedKey = Event::KeyReleased;

	//Mouse Button
	using PressedMouseButton = Event::MouseButtonPressed;
	using ReleasedMouseButton = Event::MouseButtonReleased;
	//Mouse 
	using ScrolledMouseWheel = Event::MouseWheelScrolled;
	using MovedMouse = Event::MouseMoved;
	using MovedRawMouse = Event::MouseMovedRaw;
	using EnteredMouse= Event::MouseEntered;
	using LeftMouse = Event::MouseLeft;

	//Window
	using ResizedWindow = Event::Resized;
	using LostFocus = Event::FocusLost;
	using GainedFocus = Event::FocusGained;
	using EnteredText = Event::TextEntered;
	using ClosedWindow = Event::Closed;

	//Controler
	using ControllerJoystickPressed = Event::JoystickButtonPressed;
	using ControllerJoystickReleased = Event::JoystickButtonReleased;
	using ControllerJoystickMoved = Event::JoystickMoved;
	using ControllerJoystickConnected = Event::JoystickConnected;
	using ControllerJoystickDisconnected = Event::JoystickDisconnected;

	//Screen
	using BeganTouch = Event::TouchBegan;
	using MovedTouch = Event::TouchMoved;
	using EndedTouch = Event::TouchEnded;
	using ChangedSensor = Event::SensorChanged;
	
#pragma endregion

	struct CallBackType
	{
		unique_ptr<function<void()>> digitalCallback; // bool
		unique_ptr<function<void(const float& _axis)>>	axisCallback;	 // float
		unique_ptr<function<void(const Vector2f& _axis2)>>	axis2Callback;
		CallBackType()
		{

		}
		CallBackType(const function<void()>& _digitalCallback)
		{
			digitalCallback = make_unique<function<void()>>(_digitalCallback);
		}
		CallBackType(const function<void(const float& _axis)>& _axisCallback)
		{
			axisCallback = make_unique<function<void(const float& _axis)>>(_axisCallback);
		}
		CallBackType(const function<void(const Vector2f& _axis2)>& _axis2Callback)
		{
			axis2Callback = make_unique<function<void(const Vector2f & _axis2)>>(_axis2Callback);
		}
		~CallBackType()
		{

		}
	};

	enum class ControllerButtonsType
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

	enum ActionType
	{
		//Keyboard
		KeyPressed,				//ValueType = Digital
		KeyHold,				//ValueType = Digital
		KeyReleased,			//ValueType = Digital

		//Mouse Button
		MouseButtonPressed,		//ValueType = Digital
		MouseButtonHold,		//ValueType = Digital
		MouseButtonReleased,	//ValueType = Digital
		//Mouse
		MouseWheelScrolled,		//ValueType = Axis
		MouseMoved,				//ValueType = Axis2
		MouseMovedRaw,			//ValueType = Axis2
		MouseEntered,			//ValueType = Digital
		MouseLeft,				//ValueType = Digital

		//Window
		Resized,				//ValueType = Axis2
		FocusLost,				//ValueType = Digital
		FocusGained,			//ValueType = Digital
		TextEntered,			//ValueType = Digital
		Closed,					//ValueType = Digital

		//Controller
		JoystickButtonPressed,	//ValueType = Digital
		JoystickButtonReleased,	//ValueType = Digital
		JoystickMoved,			//ValueType = Axis2
		JoystickConnected,		//ValueType = Digital
		JoystickDisconnected,	//ValueType = Digital

		//Screen
		TouchBegan,				//ValueType = Axis2
		TouchMoved,				//ValueType = Axis2
		TouchEnded,				//ValueType = Axis2
		SensorChanged,			//ValueType = Digital
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
		Digital, // type = void
		Axis,	 // type = float
		Axis2,	 // type = Vector2f
	};

	struct ActionData
	{
		ValueType value;
		ActionType type;
		int key;
		int JoystickId;

		/// <summary>
		/// Constructeur pour les ActionTypes :
		/// KeyPressed /
		/// KeyHold /
		///	KeyReleased /
		///	MouseButtonPressed /
		///	MouseButtonHold /
		///	MouseButtonReleased /
		/// MouseWheelScrolled /
		/// SensorChanged 
		/// </summary>
		/// <typeparam name="EnumType"></typeparam>
		/// <typeparam name=""></typeparam>
		/// <param name="_type"></param>
		/// <param name="_key">Clé qui doit être détecter</param>
		template<typename EnumType, typename = enable_if_t<is_enum_v<EnumType>>>
		ActionData(const ActionType& _type, const EnumType& _key)
		{
			assert((_type == KeyPressed || _type == KeyHold ||
				_type == KeyReleased || _type == MouseButtonPressed || _type == MouseButtonHold ||
				_type == MouseButtonReleased || _type == SensorChanged || _type == MouseWheelScrolled) &&
				"Invalid constructor to use this ActionType!");

			value = ComputeValueTypeWithActionType(_type);
			type = _type;
			key = CAST(int, _key);
			JoystickId = -1;
		}
		/// <summary>
		/// Constructeur pour les ActionTypes :
		/// JoystickButtonPressed /
		/// JoystickButtonReleased /
		/// JoystickMoved /
		/// JoystickConnected /
		///	JoystickDisconnected 
		/// </summary>
		/// <param name="_type"></param>
		/// <param name="_button">Boutton de Joystick</param>
		ActionData(const ActionType& _type, const int _joystick, const int _button = -1)
		{
			assert((_type == JoystickButtonPressed || _type == JoystickButtonReleased ||
				_type == JoystickMoved || _type == JoystickConnected ||
				_type == JoystickDisconnected) &&
				"Invalid constructor to use this ActionType!");

			value = ComputeValueTypeWithActionType(_type);
			type = _type;
			key = _button;
			JoystickId = _joystick;
		}
		/// <summary>
		/// Constructeur pour les ActionTypes :
		/// Closed /
		/// MouseEntered /
		/// MouseLeft /
		/// FocusLost /
		/// MouseMoved /
		/// MouseMovedRaw /
		///	MouseEntered /
		///	MouseLeft /
		///	Resized /
		///	FocusLost /
		///	FocusGained /
		///	TextEntered /
		/// TouchBegan /
		/// TouchMoved /
		///	TouchEnded /
		/// FocusGained
		/// </summary>
		/// <param name="_type"></param>
		ActionData(const ActionType& _type)
		{
			assert((_type != KeyPressed && _type != KeyHold &&
				_type != KeyReleased && _type != MouseButtonPressed && _type != MouseButtonHold &&
				_type != MouseButtonReleased && _type != SensorChanged &&
				_type != JoystickButtonPressed && _type != JoystickButtonReleased &&
				_type != JoystickMoved && _type != JoystickConnected &&
				_type != JoystickDisconnected && _type != MouseWheelScrolled) &&
				"Invalid constructor to use this ActionType!");

			value = ComputeValueTypeWithActionType(_type);
			type = _type;
			key = -1;
		}

		ValueType ComputeValueTypeWithActionType(const ActionType& _type)
		{
			switch (_type)
			{
			case MouseMoved:
			case MouseMovedRaw:
			case Resized:
			case JoystickMoved:
			case TouchBegan:
			case TouchMoved:
			case TouchEnded:
				return Axis2;
			case MouseWheelScrolled:
				return Axis;
			default:
				break;
			}
			return Digital;
		}
	};

	class Action
	{
		string name;
		multimap<TypeIndex, ActionData> allData;
		shared_ptr<CallBackType> callback;
		bool isKeyHolding;
		bool isButtonHolding;

	private:
		template<typename EnumType, typename = enable_if_t<is_enum_v<EnumType>>>
		FORCEINLINE bool IsInAllData(const TypeIndex& _type, const EnumType& _key)
		{
			return IsInAllData(_type, CAST(int, _key));
		}
		FORCEINLINE bool IsInAllData(const TypeIndex& _type, const int _key)
		{
			using Iterator = multimap<TypeIndex, ActionData>::iterator;
			const pair <Iterator, Iterator>& _actionsType = allData.equal_range(_type);
			for (Iterator _it = _actionsType.first; _it != _actionsType.second; ++_it)
			{
				if (_it->second.key == _key) return true;
			}
			return false;
		}
		FORCEINLINE bool HasJoystickIDInAllData(const TypeIndex& _type, const int _key)
		{
			using Iterator = multimap<TypeIndex, ActionData>::iterator;
			const pair <Iterator, Iterator>& _actionsType = allData.equal_range(_type);
			for (Iterator _it = _actionsType.first; _it != _actionsType.second; ++_it)
			{
				if (_it->second.key == _key) return true;
			}
			return false;
		}
		template<typename EnumType, typename = enable_if_t<is_enum_v<EnumType>>>
		FORCEINLINE bool IsSpecificTypeInAllData(const TypeIndex& _type, const EnumType& _key, const ActionType& _specificType)
		{
			return IsSpecificTypeInAllData(_type, CAST(int, _key), _specificType);
		}
		FORCEINLINE bool IsSpecificTypeInAllData(const TypeIndex& _type, const int _key, const ActionType& _specificType)
		{
			using Iterator = multimap<TypeIndex, ActionData>::iterator;
			const pair <Iterator, Iterator>& _actionsType = allData.equal_range(_type);
			for (Iterator _it = _actionsType.first; _it != _actionsType.second; ++_it)
			{
				if (_it->second.key == _key && _it->second.type == _specificType) return true;
			}
			return false;
		}
		void SimpleConstruct(const string& _name, const ActionData& _data)
		{
			name = _name;
			AddData(_data);
			isKeyHolding = false;
			isButtonHolding = false;
		}
		void MultipleConstruct(const string& _name, const vector<ActionData>& _allData)
		{
			name = _name;
			for (const ActionData& _actionData : _allData)
			{
				AddData(_actionData);
			}
			isKeyHolding = false;
			isButtonHolding = false;
		}

	public:
		FORCEINLINE string GetName() const
		{
			return name;
		}
		FORCEINLINE void AddData(const ActionData& _actionData)
		{
			allData.insert({ ComputeTypeIndexByActionType(_actionData.type), _actionData });
		}
		/*template <typename Type>
		FORCEINLINE void SetTrigger()
		{
			data.trigger = typeid(Type);
		}*/

	public:
		/// <summary>
		/// Constructeur d'action dont la ValueType est Axis2 !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Axis2</param>
		/// <param name="_callback"></param>
		Action(const string& _name, const ActionData& _data, const function<void(const Vector2f& _parameter)>& _callback);
		

		/// <summary>
		/// Constructeur d'action dont la ValueType est Axis !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Axis</param>
		/// <param name="_callback"></param>
		Action(const string& _name, const ActionData& _data, const function<void(const float _parameter)>& _callback);
		

		/// <summary>
		/// Constructeur d'action dont la ValueType est Digital !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Digital</param>
		/// <param name="_callback"></param>
		Action(const string& _name, const ActionData& _data, const function<void()>& _callback);
		
		/// <summary>
		/// Constructeur d'actions dont les ValueTypes sont Digital !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Digital</param>
		/// <param name="_callback"></param>
		Action(const string& _name, const vector<ActionData>& _allData, const function<void()>& _callback);
		
		/// <summary>
		/// Constructeur d'actions dont les ValueTypes sont Axis2 !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Axis2</param>
		/// <param name="_callback"></param>
		Action(const string& _name, const vector<ActionData>& _allData, const function<void(const Vector2f& _parameter)>& _callback);
		
		/// <summary>
		/// Constructeur d'actions dont les ValueTypes sont Axis !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Axis</param>
		/// <param name="_callback"></param>
		Action(const string& _name, const vector<ActionData>& _allData, const function<void(const float _parameter)>& _callback);
		
	public:
		void TryToExecute(const EventInfo& _event);

	private:
		TypeIndex ComputeTypeIndexByActionType(const ActionType& _typeIndex);
		
	
	};
}