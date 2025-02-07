#pragma once
#include "PanelWidget.h"
#include "CanvasSlot.h"

namespace UI
{
	class CanvasWidget : public PanelWidget
	{
	public:
		FORCEINLINE virtual bool AddChild(Widget* _widget) override
		{
			if (!Super::AddChild(_widget)) return false;

			_widget->AddSlot(new CanvasSlot(this, _widget));
			return true;
		}

	public:
		CanvasWidget(Level* _level, const string& _name, const RenderType& _type);

	public:
		virtual void Construct() override;
		virtual void Render(RenderWindow& _window) override;
	};
}