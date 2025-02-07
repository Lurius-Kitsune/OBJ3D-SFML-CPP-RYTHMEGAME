#include "CanvasWidget.h"

UI::CanvasWidget::CanvasWidget(const string& _name, const RenderType& _type) : PanelWidget(_name, _type)
{
	size = { 400.0f, 300.0f };
}

UI::CanvasWidget::~CanvasWidget()
{
}

void UI::CanvasWidget::Construct()
{
	Super::Construct();
	for (Actor* _actor : GetChildren())
	{
		if (Widget* _widget = Cast<Widget>(_actor))
		{
			_widget->Construct();
		}
	}
	if (debugMode) LOG(Warning, "DebugMode enabled on Canvas \"" + GetName() + "\"");
}

void UI::CanvasWidget::Render(RenderWindow& _window)
{
	Super::Render(_window);
}
