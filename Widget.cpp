#include "Widget.h"
#include "CameraManager.h"
#include "Level.h"

using namespace Camera;

UI::Widget::Widget(const string& _name, const RenderType& _type) : Actor(_name)
{
	type = _type;
	visibility = Visible;
	renderToken = 0;
	zOrder = 0;
}

void UI::Widget::Construct()
{
	const RenderData& _data = RenderData(bind(&Widget::Render, this, _1), type);
	renderToken = level->GetCameraManager().BindOnRenderWindow(_data, zOrder);
}

void UI::Widget::Deconstruct()
{
	level->GetCameraManager().UnbindOnRenderWindow(renderToken);
}