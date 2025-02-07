#include "HUD.h"
#include "CameraManager.h"

using namespace Camera;

UI::HUD::HUD(Level* _level) : Actor(_level)
{
	allWidgets = set<Widget*>();
	currentWidget = nullptr;
}

UI::HUD::HUD(const HUD& _other) : Actor(_other)
{
	for (Widget* _widget : _other.allWidgets)
	{
		allWidgets.insert(_widget);
	}

	currentWidget = _other.currentWidget;
}


void UI::HUD::AddToViewport(Widget* _widget)
{
	_widget->Construct();
}

void UI::HUD::RemoveFromViewport(Widget* _widget)
{
	_widget->Deconstruct();
}