#pragma once
#include "Widget.h"

namespace UI
{
	class Canvas : public Widget
	{
		set<Widget*> allWidgets;
	public:
		/*template <typename Type = Widget, IS_BASE_OF(Widget, Type)>
		FORCEINLINE void AddWidget(Type* _widget)
		{
			AddChild(_widget, AT_KEEP_RELATIVE);
		}
		template <typename Type = Widget, IS_BASE_OF(Widget, Type)>
		FORCEINLINE void RemoveWidget(Type* _widget)
		{
			RemoveChild(_widget);
		}*/

		FORCEINLINE void AddWidget(Widget* _widget)
		{
			allWidgets.insert(_widget);
		}
		FORCEINLINE void RemoveWidget(Widget* _widget)
		{
			allWidgets.erase(_widget);
		}

	public:
		Canvas(const string& _name, const RenderType& _type = Screen);

		void Render(RenderWindow& _window);

	public:
		virtual void Construct() override;
		void UpdateWidgets();
	};
}


