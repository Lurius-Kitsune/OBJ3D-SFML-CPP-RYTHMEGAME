#include "Slot.h"
#include "PanelWidget.h"

UI::Slot::Slot(PanelWidget* _parent, Widget* _content)
{
	parent = _parent;
	content = _content;
	position = _content->GetPosition();
	size = _content->GetSize();
}