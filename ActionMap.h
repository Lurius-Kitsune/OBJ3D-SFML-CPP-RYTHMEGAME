#pragma once
#include "CoreMinimal.h"
#include "Action.h"

namespace Input
{
	class ActionMap
	{
		bool isActive;
		string name;
		map<string, Action*> actions;

	public:
		FORCEINLINE void Enable()
		{
			isActive = true;
		}
		FORCEINLINE void Disable()
		{
			isActive = false;
		}

	public:
		ActionMap(const string& _name = "DefaultActionMap");
		~ActionMap();

	public:
		/// <summary>
		/// Ajoute une action dont ValueType est Digital !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Digital</param>
		/// <param name="_callback"></param>
		void AddAction(const string& _name, const ActionData& _data, const function<void()>& _callback);
		/// <summary>
		/// Ajoute une action dont ValueType est Axis2 !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Axis2</param>
		/// <param name="_callback"></param>
		void AddAction(const string& _name, const ActionData& _data, const function<void(const Vector2f& _parameter)>& _callback);
		/// <summary>
		/// Ajoute une action dont ValueType est Axis !
		/// </summary>
		/// <param name="_name">nom de l'action</param>
		/// <param name="_data">ActionData dont la ValueType est Axis</param>
		/// <param name="_callback"></param>
		void AddAction(const string& _name, const ActionData& _data, const function<void(const float _parameter)>& _callback);

		void AddActions(const vector<Action*>& _actions);
		void RemoveAction(const string& _name);
		void Update(const EventInfo& _event);
	};
}