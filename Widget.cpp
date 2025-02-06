#include "Widget.h"
#include "LevelManager.h"

using namespace Camera;

UI::Widget::Widget(const string& _name, const RenderType& _type) : Actor(_name)
{
	type = _type;
	visibility = Visible;
	renderToken = 0;
	zOrder = 0;
	slot = new Slot({}, {});
}

UI::Widget::~Widget()
{
	delete slot;
}

void UI::Widget::Construct()
{
	const RenderData& _data = RenderData(bind(&Widget::Render, this, _1), type);
	renderToken = M_LEVEL.GetCurrentLevel()->GetCameraManager().BindOnRenderWindow(_data, zOrder);
}

void UI::Widget::Deconstruct()
{
	M_LEVEL.GetCurrentLevel()->GetCameraManager().UnbindOnRenderWindow(renderToken);
}