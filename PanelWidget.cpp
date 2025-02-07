#include "PanelWidget.h"

UI::PanelWidget::PanelWidget(const string& _name, const RenderType& _type) : Widget(_name, _type)
{
	maxChild = 32768;
	size = { 64.0f, 64.0f };
	debugMode = false;
	debugFrame = VertexArray(PrimitiveType::LineStrip, 5);
	debugFrame[0].color = Color(255, 0, 0);
	debugFrame[1].color = Color(255, 255, 0);
	debugFrame[2].color = Color(0, 255, 0);
	debugFrame[3].color = Color(255, 255, 0);
	debugFrame[4].color = Color(255, 0, 0);
	UpdateDebugFrame();
}

UI::PanelWidget::~PanelWidget()
{

}

void UI::PanelWidget::Render(RenderWindow& _window)
{
	if (debugMode)
	{
		_window.draw(debugFrame);
	}
}

void UI::PanelWidget::UpdateDebugFrame()
{
	debugFrame[0].position = Vector2f(GetPosition());
	debugFrame[1].position = Vector2f(size.x, GetPosition().y);
	debugFrame[2].position = Vector2f(size.x, size.y);
	debugFrame[3].position = Vector2f(GetPosition().x, size.y);
	debugFrame[4].position = debugFrame[0].position;
}
