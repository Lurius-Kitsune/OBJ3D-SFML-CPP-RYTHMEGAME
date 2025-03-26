#include "Slot.h"
#include "PanelWidget.h"

UI::Slot::Slot(PanelWidget* _parent, Widget* _content)
{
	parent = _parent;
	content = _content;
	position = _content->GetPosition();
	size = _content->GetSize();
	debugMode = false;
	debugFrame = VertexArray(PrimitiveType::LineStrip, 5);
	debugFrame[0].color = Color(255, 0, 0);
	debugFrame[1].color = Color(255, 255, 0);
	debugFrame[2].color = Color(0, 255, 0);
	debugFrame[3].color = Color(0, 255, 255);
	debugFrame[4].color = Color(0, 0, 255);

	UpdateDebugFrame();
}

void UI::Slot::RenderDebugFrame(RenderWindow& _window)
{
	if (debugMode)
	{
		UpdateDebugFrame();
		_window.draw(debugFrame);
	}
}

void UI::Slot::UpdateDebugFrame()
{
	debugFrame[0].position = Vector2f(parent->GetScale().x * position.x, parent->GetScale().y * position.y);
	debugFrame[1].position = Vector2f(parent->GetScale().x * (position.x + size.x), parent->GetScale().x * position.y);
	debugFrame[2].position = Vector2f(parent->GetScale().x * (position.x + size.x), parent->GetScale().y * (position.y + size.y));
	debugFrame[3].position = Vector2f(parent->GetScale().x * position.x, parent->GetScale().y * (position.y + size.y));
	debugFrame[4].position = debugFrame[0].position;
}

void UI::Slot::UpdateDebugMode(const bool _status)
{
	if (_status != debugMode && _status)
	{
		LOG(Warning, "DebugMode enabled on Slot of \"" + content->GetName() + "\"");
	}
	else if (_status != debugMode && !_status)
	{
		LOG(Warning, "DebugMode disabled on Slot of \"" + content->GetName() + "\"");

	}
	debugMode = _status;
}

