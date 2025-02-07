#include "Action.h"
#include "InputManager.h"

Input::Action::Action(const string& _name, const ActionData& _data, const function<void(const Vector2f& _parameter)>& _callback)
{
	assert(_data.value == Axis2 &&
		"The callback must be a function with compatible parameter like ValueType return !");
	SimpleConstruct(_name, _data);
	callback = make_shared<CallBackType>(_callback);
}
Input::Action::Action(const string& _name, const ActionData& _data, const function<void(const float _parameter)>& _callback)
{
	assert(_data.value == Axis &&
		"The callback must be a function with compatible parameter like ValueType return !");
	SimpleConstruct(_name, _data);
	callback = make_shared<CallBackType>(_callback);
}
Input::Action::Action(const string& _name, const ActionData& _data, const function<void()>& _callback)
{
	assert(_data.value == Digital &&
		"The callback must be a function with compatible parameter like ValueType return !");

	SimpleConstruct(_name, _data);
	callback = make_shared<CallBackType>(_callback);
}
Input::Action::Action(const string& _name, const vector<ActionData>& _allData, const function<void()>& _callback)
{
	if (_allData.empty()) return;

	assert(_allData[0].value == Digital &&
		"The callback must be a function with compatible parameter like ValueType return !");

	MultipleConstruct(_name, _allData);
	callback = make_shared<CallBackType>(_callback);
}
Input::Action::Action(const string& _name, const vector<ActionData>& _allData, const function<void(const Vector2f& _parameter)>& _callback)
{
	if (_allData.empty()) return;

	assert(_allData[0].value == Axis2 &&
		"The callback must be a function with compatible parameter like ValueType return !");

	MultipleConstruct(_name, _allData);
	callback = make_shared<CallBackType>(_callback);
}
Input::Action::Action(const string& _name, const vector<ActionData>& _allData, const function<void(const float _parameter)>& _callback)
{
	if (_allData.empty()) return;

	assert(_allData[0].value == Axis2 &&
		"The callback must be a function with compatible parameter like ValueType return !");

	MultipleConstruct(_name, _allData);
	callback = make_shared<CallBackType>(_callback);
}

void Input::Action::TryToExecute(const EventInfo& _event)
{
	_event->visit([&](auto&& _element)
		{
			const type_index& _elementType = TYPE_ID(_element);

			if (allData.contains(_elementType))
			{
#pragma region Keyboard


				if (_event->is<PressedKey>())
				{
					const bool _isKeyHolding = /*isKeyHolding*/ M_INPUT.GetIsKeyHolding();
					using Iterator = multimap<TypeIndex, ActionData>::iterator;
					const pair <Iterator, Iterator>& _actionsType = allData.equal_range(_elementType);
					for (Iterator _it = _actionsType.first; _it != _actionsType.second; ++_it)
					{
						if (Keyboard::isKeyPressed(CAST(Key, _it->second.key)))
						{
							if (_it->second.type == KeyHold ||
								(!_isKeyHolding && _it->second.type == KeyPressed))
							{
								(*callback.get()->digitalCallback.get())();
								break;
							}
						}
					}
				}

				if (const ReleasedKey* _key = _event->getIf<ReleasedKey>())
				{
					if (IsInAllData(_elementType, CAST(const int, _key->code)))
					{
						(*callback.get()->digitalCallback.get())();
					}
				}


#pragma endregion

#pragma region Mouse
#pragma region Button

				else if (_event->is<PressedMouseButton>())
				{
					const bool _isButtonHolding = M_INPUT.GetIsButtonHolding();
					using Iterator = multimap<TypeIndex, ActionData>::iterator;
					const pair <Iterator, Iterator>& _actionsType = allData.equal_range(_elementType);
					for (Iterator _it = _actionsType.first; _it != _actionsType.second; ++_it)
					{
						if (Mouse::isButtonPressed(CAST(Mouse::Button, _it->second.key)))
						{
							if ( _it->second.type == MouseButtonHold ||
								(!_isButtonHolding && _it->second.type == MouseButtonPressed))
							{
								(*callback.get()->digitalCallback.get())();
								break;
							}
						}
					}
				}

				else if (const ReleasedMouseButton* _key = _event->getIf<ReleasedMouseButton>())
				{
					if (IsInAllData(_elementType, CAST(const int, _key->button)))
					{
						(*callback.get()->digitalCallback.get())();
					}
				}
#pragma endregion

				//TODO rajouter condition appel callback
				else if (const ScrolledMouseWheel* _key = _event->getIf<ScrolledMouseWheel>())
				{
					if (IsInAllData(_elementType, _key->wheel))
					{
						(*callback.get()->axisCallback.get())(_key->delta);
					}
				}
				else if (const MovedMouse* _key = _event->getIf<MovedMouse>())
				{
					(*callback.get()->axis2Callback.get())(CAST(Vector2f, _key->position));
				}
				else if (const MovedRawMouse* _key = _event->getIf<MovedRawMouse>())
				{
					(*callback.get()->axis2Callback.get())(CAST(Vector2f, _key->delta));
				}
				else if (_event->is<EnteredMouse>())
				{
					(*callback.get()->digitalCallback.get())();
				}
				else if (_event->is<LeftMouse>())
				{
					(*callback.get()->digitalCallback.get())();
				}
#pragma endregion

#pragma region Window
				else if (const ResizedWindow* _key = _event->getIf<ResizedWindow>())
				{
					(*callback.get()->axis2Callback.get())(CAST(Vector2f, _key->size));
				}
				else if (_event->is<LostFocus>())
				{
					(*callback.get()->digitalCallback.get())();
				}
				else if (_event->is<GainedFocus>())
				{
					(*callback.get()->digitalCallback.get())();
				}
				else if (const EnteredText* _key = _event->getIf<EnteredText>())
				{
					(*callback.get()->digitalCallback.get())();
				}
				else if (const ClosedWindow* _key = _event->getIf<ClosedWindow>())
				{
					(*callback.get()->digitalCallback.get())();
				}
#pragma endregion

#pragma region Controler
				else if (const ControllerJoystickPressed* _key = _event->getIf<ControllerJoystickPressed>())
				{
					if (HasJoystickIDInAllData(_elementType, _key->joystickId))
					{
						const bool _isJoystickButtonHolding = M_INPUT.GetIsJoystickButtonHolding();
						using Iterator = multimap<TypeIndex, ActionData>::iterator;
						const pair <Iterator, Iterator>& _actionsType = allData.equal_range(_elementType);
						for (Iterator _it = _actionsType.first; _it != _actionsType.second; ++_it)
						{
							if (Joystick::isButtonPressed(_key->joystickId, _it->second.key))
							{
								if (_it->second.type == JoystickButtonHold ||
									(!_isJoystickButtonHolding
										&& _it->second.type == JoystickButtonPressed))
								{
									(*callback.get()->digitalCallback.get())();
									break;
								}
							}
						}
					}
				}
				else if (const ControllerJoystickReleased* _key = _event->getIf<ControllerJoystickReleased>())
				{
					if (HasJoystickIDInAllData(_elementType, _key->joystickId) && 
						IsInAllData(_elementType, _key->button))
					{
						(*callback.get()->digitalCallback.get())();
					}
				}
				else if (const ControllerJoystickMoved* _key = _event->getIf<ControllerJoystickMoved>())
				{
					if (HasJoystickIDInAllData(_elementType, _key->joystickId) &&
						IsInAllData(_elementType, _key->axis))
					{
						(*callback.get()->axisCallback.get())(_key->position);
					}
				}
				else if (const ControllerJoystickConnected* _key = _event->getIf<ControllerJoystickConnected>())
				{
					if (HasJoystickIDInAllData(_elementType, _key->joystickId))
					{
						(*callback.get()->digitalCallback.get())();
					}
				}
				else if (const ControllerJoystickDisconnected* _key = _event->getIf<ControllerJoystickDisconnected>())
				{
					if (HasJoystickIDInAllData(_elementType, _key->joystickId))
					{
						(*callback.get()->digitalCallback.get())();
					}
				}
#pragma endregion

#pragma region Screen
				else if (const BeganTouch* _key = _event->getIf<BeganTouch>())
				{
					(*callback.get()->axis2Callback.get())(CAST(Vector2f, _key->position));
				}
				else if (const MovedTouch* _key = _event->getIf<MovedTouch>())
				{
					(*callback.get()->axis2Callback.get())(CAST(Vector2f, _key->position));
				}
				else if (const EndedTouch* _key = _event->getIf<EndedTouch>())
				{
					(*callback.get()->axis2Callback.get())(CAST(Vector2f, _key->position));
				}
				else if (const ChangedSensor* _key = _event->getIf<ChangedSensor>())
				{
					if (IsInAllData(_elementType, _key->type))
					{
						(*callback.get()->digitalCallback.get())();
					}
				}
#pragma endregion

			}
		});
}

Input::TypeIndex Input::Action::ComputeTypeIndexByActionType(const ActionType& _actionType)
{
	const vector<function<TypeIndex()>>& _actionsTypes =
	{
		//Keyboard
		[&]() { return type_index(TYPE_ID(PressedKey)); },						//KeyPressed
		[&]() { return type_index(TYPE_ID(PressedKey)); },						//KeyHold
		[&]() { return type_index(TYPE_ID(ReleasedKey)); },						//KeyReleased

		//Mouse Button
		[&]() { return type_index(TYPE_ID(PressedMouseButton)); },				//MouseButtonPressed
		[&]() { return type_index(TYPE_ID(PressedMouseButton)); },				//MouseButtonHold
		[&]() { return type_index(TYPE_ID(ReleasedMouseButton)); },				//MouseButtonReleased
		//Mouse 
		[&]() { return type_index(TYPE_ID(ScrolledMouseWheel)); },				//MouseWheelScrolled
		[&]() { return type_index(TYPE_ID(MovedMouse)); },						//MouseMoved
		[&]() { return type_index(TYPE_ID(MovedRawMouse)); },					//MouseMovedRaw
		[&]() { return type_index(TYPE_ID(EnteredMouse)); },					//MouseEntered
		[&]() { return type_index(TYPE_ID(LeftMouse)); },						//MouseLeft

		//Window
		[&]() { return type_index(TYPE_ID(ResizedWindow)); },					//Resized
		[&]() { return type_index(TYPE_ID(LostFocus)); },						//FocusLost
		[&]() { return type_index(TYPE_ID(GainedFocus)); },						//FocusGained
		[&]() { return type_index(TYPE_ID(EnteredText)); },						//TextEntered
		[&]() { return type_index(TYPE_ID(ClosedWindow)); },  					//Closed

		//Controler
		[&]() { return type_index(TYPE_ID(ControllerJoystickPressed)); },		//JoystickButtonPressed
		[&]() { return type_index(TYPE_ID(ControllerJoystickPressed)); },		//JoystickButtonHold
		[&]() { return type_index(TYPE_ID(ControllerJoystickReleased)); },		//JoystickButtonReleased
		[&]() { return type_index(TYPE_ID(ControllerJoystickMoved)); },			//JoystickMoved
		[&]() { return type_index(TYPE_ID(ControllerJoystickConnected)); },		//JoystickConnected
		[&]() { return type_index(TYPE_ID(ControllerJoystickDisconnected)); },	//JoystickDisconnected

		//Screen
		[&]() { return type_index(TYPE_ID(BeganTouch)); },						//TouchBegan
		[&]() { return type_index(TYPE_ID(MovedTouch)); },						//TouchMoved
		[&]() { return type_index(TYPE_ID(EndedTouch)); },						//TouchEnded
		[&]() { return type_index(TYPE_ID(ChangedSensor)); }					//SensorChanged
	};

	return _actionsTypes[_actionType]();
}