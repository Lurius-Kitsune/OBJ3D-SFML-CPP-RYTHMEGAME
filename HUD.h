#pragma once
#include "Singleton.h"
#include "Widget.h"

namespace UI
{
	class HUD : public Singleton<HUD>
	{
		set<Widget*> allWidgets;
		Widget* currentWidget;

		FORCEINLINE void RegisterWidget(Widget* _widget)
		{
			if (allWidgets.contains(_widget)) return;
			allWidgets.insert(_widget);
		}
	public:
		template <typename Type, typename ...Args, IS_BASE_OF(Widget, Type)>
		FORCEINLINE Type* CreateWidget(Args... _args)
		{
			Type* _widget = new Type(_args...);
			RegisterWidget(_widget);
			return _widget;
		}
		FORCEINLINE void UnregisterWidget(Widget* _widget)
		{
			if (!allWidgets.contains(_widget)) return;
			allWidgets.erase(_widget);
		}

	public:
		HUD();
		~HUD();

	public:
		void AddToViewport(Widget* _widget);
		void RemoveFromViewport(Widget* _widget);
	};
}