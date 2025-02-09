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

		FORCEINLINE virtual void SetVisibility(const VisibilityType& _visibility) override
		{
			Super::SetVisibility(_visibility);
			for (Slot* _slot : GetSlots())
			{
				_slot->GetContent()->SetVisibility(_visibility);
			}
		}
	public:
		CanvasWidget(Level* _level, const string& _name = "Canvas", const RenderType& _type = Screen);

	public:
		virtual void Construct() override;
		virtual void Render(RenderWindow& _window) override;
	};
}