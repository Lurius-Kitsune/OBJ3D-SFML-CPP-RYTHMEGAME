#include "ActionMap.h"

Input::ActionMap::ActionMap(const string& _name)
{
	isActive = false;
	name = _name;
	actions = map<string, Action*>();
}

Input::ActionMap::~ActionMap()
{
	for (const pair<string, Action*>& _pair : actions)
	{
		delete _pair.second;
	}
}


void Input::ActionMap::AddAction(const string& _name, const ActionData& _data, const function<void()>& _callback)
{
	assert(_data.value == Digital &&
		"The callback must be a function with compatible parameter like ValueType return !");

	if (actions.contains(_name))
	{
		LOG(Error, "This Action's name (" + _name + ") already used in this ActionMap ("+ name + ") !");
		return;
	}

	Action* _action = new Action(_name, _data, _callback);
	actions.insert({ _action->GetName(), _action });
}
void Input::ActionMap::AddAction(const string& _name, const ActionData& _data, const function<void(const Vector2f& _parameter)>& _callback)
{
	assert(_data.value == Axis2 &&
		"The callback must be a function with compatible parameter like ValueType return !");

	if (actions.contains(_name))
	{
		LOG(Error, "This Action's name (" + _name + ") already used in this ActionMap (" + name + ") !");
		return;
	}

	Action* _action = new Action(_name, _data, _callback);
	actions.insert({ _action->GetName(), _action });
}

void Input::ActionMap::AddAction(const string& _name, const ActionData& _data, const function<void(const float _parameter)>& _callback)
{
	assert(_data.value == Axis &&
		"The callback must be a function with compatible parameter like ValueType return !");

	if (actions.contains(_name))
	{
		LOG(Error, "This Action's name (" + _name + ") already used in this ActionMap (" + name + ") !");
		return;
	}

	Action* _action = new Action(_name, _data, _callback);
	actions.insert({ _action->GetName(), _action });
}
void Input::ActionMap::AddActions(const vector<Action*>& _actions)
{
	for (Action* _action : _actions)
	{
		actions.insert({ _action->GetName(), _action });
	}
}

void Input::ActionMap::RemoveAction(const string& _name)
{
	if (!actions.contains(_name)) return;

	delete actions.at(_name);
	actions.erase(_name);
}

void Input::ActionMap::Update(const EventInfo& _event)
{
	if (!isActive) return;

	for (const pair<string, Action*>& _action : actions)
	{
		_action.second->TryToExecute(_event);
	}
}