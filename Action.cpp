#include "Action.h"

Input::Action::Action(const string& _name, const ActionData& _data, const function<void()>& _callback)
{
	
}

Input::Action::Action(const string& _name, const set<ActionData>& _allData, const function<void()>& _callback)
{
	name = _name;
	//allData = _allData;
	callback = _callback;
}


void Input::Action::TryToExecute(const EventInfo& _event)
{
	if (!callback) return;

	_event->visit([&](auto&& _element)
	{
		const type_index& _elementType = TYPE_ID(_element);

		/*if (_elementType == data.trigger)
		{
			if (const KeyPressed* _key = _event->getIf<KeyPressed>())
			{
				if (allData.contains(CAST(const int, _key->code)))
				{
					callback();
				}
			}

			else if (const KeyReleased* _key = _event->getIf<KeyReleased>())
			{
				if (allData.contains(CAST(const int, _key->code)))
				{
					callback();
				}
			}
		}*/
	});
}