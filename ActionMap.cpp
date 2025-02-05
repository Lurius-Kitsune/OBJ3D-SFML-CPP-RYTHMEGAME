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


void Input::ActionMap::AddAction(Action* _action)
{
	actions.insert({ _action->GetName(), _action });
}

void Input::ActionMap::AddActions(const vector<Action*>& _actions)
{
	for (Action* _action : _actions)
	{
		AddAction(_action);
	}
}

void Input::ActionMap::Update(const EventInfo& _event)
{
	if (!isActive) return;

	for (const pair<string, Action*>& _action : actions)
	{
		_action.second->TryToExecute(_event);
	}
}