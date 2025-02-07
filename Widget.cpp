#include "Widget.h"
#include "CameraManager.h"
#include "Level.h"

using namespace Camera;

UI::Widget::Widget(Level* _level, const string& _name, const RenderType& _type) : Actor(_level, _name)
{
	type = _type;
	visibility = Visible;
	renderToken = 0;
	zOrder = 0;
	slot = nullptr;
}

UI::Widget::Widget(const Widget& _other)
	: Actor(_other)
{
	type = _other.type;
	visibility = _other.visibility;
	renderToken = 0;
	zOrder = _other.zOrder;
	slot = nullptr;
}

UI::Widget::~Widget()
{
	delete slot;
}


void UI::Widget::Construct()
{
	Super::Construct();

	const RenderData& _data = RenderData(bind(&Widget::Render, this, _1), type);
	renderToken = level->GetCameraManager().BindOnRenderWindow(_data, zOrder);
}

void UI::Widget::Deconstruct()
{
	Super::Deconstruct();

	level->GetCameraManager().UnbindOnRenderWindow(renderToken);
}