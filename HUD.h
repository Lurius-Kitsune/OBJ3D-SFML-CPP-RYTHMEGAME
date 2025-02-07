#pragma once
#include "Actor.h"
#include "Widget.h"

namespace UI
{
	class HUD : public Actor
	{
		set<Widget*> allWidgets;
		Widget* currentWidget;

	public:
		FORCEINLINE void RegisterWidget(Widget* _widget)
		{
			if (allWidgets.contains(_widget)) return;
			allWidgets.insert(_widget);
		}
		FORCEINLINE void UnregisterWidget(Widget* _widget)
		{
			if (!allWidgets.contains(_widget)) return;
			allWidgets.erase(_widget);
		}

	public:
		HUD(Level* _level);
		HUD(const HUD& _other);

	public:
		void AddToViewport(Widget* _widget);
		void RemoveFromViewport(Widget* _widget);
	};
}