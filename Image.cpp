#include "Image.h"

UI::Image::Image(const string& _name, const RectangleShapeData& _data, const RenderType& _type) : Widget(_name, _type)
{
	image = new ShapeObject(_data);
	sizeToContent = false;
	initialSize = _data.size;
}

void UI::Image::UpdateSize()
{
	if (sizeToContent)
	{
		SetScale(CAST(Vector2f, image->GetTexture().getSize()));
	}
	else
	{
		SetPosition(initialSize);
	}
}

void UI::Image::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	_window.draw(*image->GetDrawable());
}
