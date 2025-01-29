#include "HUD.h"
#include "CameraManager.h"

using namespace Camera;

UI::HUD::HUD()
{
	allWidgets = set<Widget*>();
	currentWidget = nullptr;
}

UI::HUD::~HUD()
{
	for (Widget* _widget : allWidgets)
	{
		delete _widget;
	}
}


void UI::HUD::AddToViewport(Widget* _widget)
{
	_widget->Construct();
}

void UI::HUD::RemoveFromViewport(Widget* _widget)
{
	_widget->Deconstruct();
}