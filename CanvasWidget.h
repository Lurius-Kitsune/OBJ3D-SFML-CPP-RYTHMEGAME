#pragma once
#include "PanelWidget.h"
#include "CanvasSlot.h"

namespace UI
{
	class CanvasWidget : public PanelWidget
	{
	public:
		template <typename Type, typename ...Args, IS_BASE_OF(Widget, Type)>
		FORCEINLINE void AddChild(Type* _widget)
		{
			if (!CanAddMoreChildren()) return;
			Actor::AddChild(_widget, AT_KEEP_RELATIVE);
			_widget->AddSlot(new CanvasSlot(this, _widget));
		}

	public:
		CanvasWidget(const string& _name, const RenderType& _type);
		~CanvasWidget();

	public:
		virtual void Construct() override;
		virtual void Render(RenderWindow& _window) override;
	};
}


