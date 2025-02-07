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
		JoystickButtonHold,		//ValueType = Digital
		JoystickButtonReleased,	//ValueType = Digital
		JoystickMoved,			//ValueType = Axis
		JoystickConnected,		//ValueType = Digital
		JoystickDisconnected,	//ValueType = Digital

		//Screen
		TouchBegan,				//ValueType = Axis2
		TouchMoved,				//ValueType = Axis2
		TouchEnded,				//ValueType = Axis2
		SensorChanged,			//ValueType = Digital
	};


	enum ValueType
	{
		Digital, // type = void
		Axis,	 // type = float
		Axis2,	 // type = Vector2f
		Axis3,	 // type = Vector3f
	};

	enum KeyType
	{
		//MOUSE
		Left,		//!< The left mouse button
		Right,		//!< The right mouse button
		Middle,		//!< The middle (wheel) mouse button
		Extra1,		//!< The first extra mouse button
		Extra2,		//!< The second extra mouse button

		//WHEEL
		Vertical = 0,	//!< The vertical mouse wheel
		Horizontal,		//!< The horizontal mouse wheel

		//KEY
		Unknown = -1, //!< Unhandled key
		A = 0,		  //!< The A key
		B,            //!< The B key
		C,            //!< The C key
		D,            //!< The D key
		E,            //!< The E key
		F,            //!< The F key
		G,            //!< The G key
		H,            //!< The H key
		I,            //!< The I key
		J,            //!< The J key
		K,            //!< The K key
		L,            //!< The L key
		M,            //!< The M key
		N,            //!< The N key
		O,            //!< The O key
		P,            //!< The P key
		Q,            //!< The Q key
		R,            //!< The R key
		S,            //!< The S key
		T,            //!< The T key
		U,            //!< The U key
		V,            //!< The V key
		W,            //!< The W key
		X,            //!< The X key
		Y,            //!< The Y key
		Z,            //!< The Z key
		Num0,         //!< The 0 key
		Num1,         //!< The 1 key
		Num2,         //!< The 2 key
		Num3,         //!< The 3 key
		Num4,         //!< The 4 key
		Num5,         //!< The 5 key
		Num6,         //!< The 6 key
		Num7,         //!< The 7 key
		Num8,         //!< The 8 key
		Num9,         //!< The 9 key
		Escape,       //!< The Escape key
		LControl,     //!< The left Control key
		LShift,       //!< The left Shift key
		LAlt,         //!< The left Alt key
		LSystem,      //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...
		RControl,     //!< The right Control key
		RShift,       //!< The right Shift key
		RAlt,         //!< The right Alt key
		RSystem,      //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
		Menu,         //!< The Menu key
		LBracket,     //!< The [ key
		RBracket,     //!< The ] key
		Semicolon,    //!< The ; key
		Comma,        //!< The , key
		Period,       //!< The . key
		Apostrophe,   //!< The ' key
		Slash,        //!< The / key
		Backslash,    //!< The \ key
		Grave,        //!< The ` key
		Equal,        //!< The = key
		Hyphen,       //!< The - key (hyphen)
		Space,        //!< The Space key
		Enter,        //!< The Enter/Return keys
		Backspace,    //!< The Backspace key
		Tab,          //!< The Tabulation key
		PageUp,       //!< The Page up key
		PageDown,     //!< The Page down key
		End,          //!< The End key
		Home,         //!< The Home key
		Insert,       //!< The Insert key
		Delete,       //!< The Delete key
		Add,          //!< The + key
		Subtract,     //!< The - key (minus, usually from numpad)
		Multiply,     //!< The * key
		Divide,       //!< The / key
		Left_Arrow,         //!< Left arrow
		Right_Arrow,        //!< Right arrow
		Up_Arrow,           //!< Up arrow
		Down_Arrow,         //!< Down arrow
		Numpad0,      //!< The numpad 0 key
		Numpad1,      //!< The numpad 1 key
		Numpad2,      //!< The numpad 2 key
		Numpad3,      //!< The numpad 3 key
		Numpad4,      //!< The numpad 4 key
		Numpad5,      //!< The numpad 5 key
		Numpad6,      //!< The numpad 6 key
		Numpad7,      //!< The numpad 7 key
		Numpad8,      //!< The numpad 8 key
		Numpad9,      //!< The numpad 9 key
		F1,           //!< The F1 key
		F2,           //!< The F2 key
		F3,           //!< The F3 key
		F4,           //!< The F4 key
		F5,           //!< The F5 key
		F6,           //!< The F6 key
		F7,           //!< The F7 key
		F8,           //!< The F8 key
		F9,           //!< The F9 key
		F10,          //!< The F10 key
		F11,          //!< The F11 key
		F12,          //!< The F12 key
		F13,          //!< The F13 key
		F14,          //!< The F14 key
		F15,          //!< The F15 key
		Pause,        //!< The Pause key

		//SENSOR
		Accelerometer = 0,	//!< Measures the raw acceleration (m/s^2)
		Gyroscope,			//!< Measures the raw rotation rates (radians/s)
		Magnetometer,		//!< Measures the ambient magnetic field (micro-teslas)
		Gravity,			//!< Measures the direction and intensity of gravity, independent of device acceleration (m/s^2)
		UserAcceleration,	//!< Measures the direction and intensity of device acceleration, independent of the gravity (m/s^2)
		Orientation,		//!< Measures the absolute 3D orientation (radians)

		//CONTROLLER
		Joystick_X = 0,		//!< The X axis = LeftJoystickX
		Joystick_Y,			//!< The Y axis = LeftJoystickY
		Joystick_Z,			//!< The Z axis = BackButtons
		Joystick_R,			//!< The R axis
		Joystick_U,			//!< The U axis = RightJoystickX
		Joystick_V,			//!< The V axis = RightJoystickY
		Joystick_PovX,		//!< The X axis of the point-of-view hat = D_PadX
		Joystick_PovY,		//!< The Y axis of the point-of-view hat = D_PadY

		LeftJoystickX = 0, // Left : -100 - 0 / Right : 0 - 100
		LeftJoystickY, // Up : -100 - 0 / Down : 0 - 100
		BackButtons = 3, // 0 - 100 : LT / -100 - 0 : RT (Xbox Controller)
		RightJoystickX, // Left : -100 - 0 / Right : 0 - 100
		RightJoystickY, // Up : -100 - 0 / Down : 0 - 100
		D_PadX, // Left = -100 / Right = 100
		D_PadY // D-Pad : Up = -100 / Down = 100
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
				_type == MouseButtonReleased || _type == SensorChanged || _type == MouseWheelScrolled ) &&
				"Invalid constructor to use this ActionType!");

			value = ComputeValueTypeWithActionType(_type);
			type = _type;
			key = CAST(int, _key);
			JoystickId = -1;
		}
		/// <summary>
		/// Constructeur pour l'ActionType :
		/// JoystickMoved 
		/// </summary>
		/// <param name="_type"></param>
		/// <param name="_key">Axis du joystick</param>
		template<typename EnumType, typename = enable_if_t<is_enum_v<EnumType>>>
		ActionData(const ActionType& _type, const int _joystickID, const EnumType& _key)
		{
			assert(_type == JoystickMoved &&
				"Invalid constructor to use this ActionType!");

			value = ComputeValueTypeWithActionType(_type);
			type = _type;
			key = CAST(int, _key);
			JoystickId = _joystickID;
		}
		/// <summary>
		/// Constructeur pour les ActionTypes :
		/// JoystickButtonPressed /
		/// JoystickButtonReleased /
		/// JoystickConnected /
		///	JoystickDisconnected 
		/// </summary>
		/// <param name="_type"></param>
		/// <param name="_button">Boutton de Joystick</param>
		ActionData(const ActionType& _type, const int _joystickID, const int _button = -1)
		{
			assert((_type == JoystickButtonPressed || _type == JoystickButtonReleased ||
				_type == JoystickConnected || _type == JoystickDisconnected) &&
				"Invalid constructor to use this ActionType!");

			value = ComputeValueTypeWithActionType(_type);
			type = _type;
			key = _button;
			JoystickId = _joystickID;
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
			case TouchBegan:
			case TouchMoved:
			case TouchEnded:
				return Axis2;
			case JoystickMoved:
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
		}
		void MultipleConstruct(const string& _name, const vector<ActionData>& _allData)
		{
			name = _name;
			for (const ActionData& _actionData : _allData)
			{
				AddData(_actionData);
			}
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