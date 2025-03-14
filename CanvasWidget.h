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
			if (!RegisterSlot(_widget)) return false;

			_widget->AddSlot(new CanvasSlot(this, _widget));
			return true;
		}
		FORCEINLINE CanvasSlot* GetSlotByWidget(Widget* _widget)
		{
			if (CanvasSlot* _slot = Cast<CanvasSlot>(_widget->GetSlot()))
			{
				return _slot;
			}
			return nullptr;
		}

	public:
		CanvasWidget(Level* _level, const string& _name = "Canvas", const RenderType& _type = Screen);

	public:
		virtual void Construct() override;
		virtual void Render(RenderWindow& _window) override;
	};
}

///////////////////////////////////////
///			CanvasWidget TUTO		///
///////////////////////////////////////
//
// Step 1	: Create Widget you want to add to the Canvas (Image, Label, ect...)
// Step 2	: Create the Canvas and choose the Size (default : 400x300)
// Step 2.5 : If you want help, you can SetDebugMode to see the Canvas border
// Step 3	: Add the Widget to the Canvas with AddChild
// Step 4	: Move the Widget into your Canvas with SetPosition (Relative)
// Step 5	: Display the Canvas with AddToViewport from HUD
//
// Bonus	: If you want to see the Slot border like the canvas, you can with this :
//			  ->	for (Slot* _slot : canvas->GetSlots())
//					{
//						_slot->SetDebugMode(true);
//					}
//
///////////////////////////////////////
///			END OF THE TUTO			///
///////////////////////////////////////