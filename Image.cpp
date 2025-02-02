#include "Image.h"

UI::Image::Image(const string& _name, const RectangleShapeData& _data, const RenderType& _type) : Widget(_name, _type)
{
	image = new ShapeObject(_data);
	sizeToContent = false;
	initialSize = _data.size;
	gradient = VertexArray(PrimitiveType::TriangleStrip, 4);
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

void UI::Image::UpdateGradient()
{
	gradient[0].position = GetPosition();
	gradient[0].color = colorGradient.topLeft;

	gradient[1].position = { GetPosition().x, GetScale().y };
	gradient[1].color = colorGradient.topRight;

	gradient[2].position = GetScale();
	gradient[2].color = colorGradient.bottomLeft;

	gradient[3].position = { GetScale().x, GetPosition().y };
	gradient[3].color = colorGradient.bottomRight;
}

void UI::Image::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	_window.draw(*image->GetDrawable());
	_window.draw(gradient);
}

void UI::Image::SetSizeToContent(const bool _status)
{
	sizeToContent = _status;
	UpdateSize();
}

void UI::Image::SetGradient(const Gradient& _gradient)
{
	colorGradient = _gradient;
	UpdateGradient();
}
