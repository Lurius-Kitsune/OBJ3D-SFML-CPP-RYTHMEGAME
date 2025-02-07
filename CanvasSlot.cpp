#include "CanvasSlot.h"
#include "PanelWidget.h"
#include "ImageWidget.h"

UI::CanvasSlot::CanvasSlot(PanelWidget* _parent, Widget* _content) : Slot(_parent, _content)
{
	fillToContent = false;
	zOrder = _parent->GetZOrder();
}

void UI::CanvasSlot::UpdateContent()
{
	if (ImageWidget* _image = Cast<ImageWidget>(content))
	{
		_image->SetSizeToContent(fillToContent);
	}
}
