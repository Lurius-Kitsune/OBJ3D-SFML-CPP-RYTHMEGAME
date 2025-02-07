#include "ImageWidget.h"
#include "Level.h"
#include "TextureManager.h"

#include "PanelWidget.h"

UI::ImageWidget::ImageWidget(const string& _name, const RectangleShapeData& _data, const RenderType& _type)
	: Widget(_name, _type)
{
	image = new MeshActor(_data, _name);
	SetTexture(_data.path);
	initialSize = GetSize();
}

UI::ImageWidget::ImageWidget(const string& _name, const CircleShapeData& _data, const RenderType& _type)
	: Widget(_name, _type)
{
	image = new MeshActor(_data.radius, _data.pointCount, _data.path, _data.rect, _name);
	SetTexture(_data.path);
}

UI::ImageWidget::~ImageWidget()
{
	delete image;
}

void UI::ImageWidget::UpdateGradient()
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

void UI::ImageWidget::UpdatePosition(const Vector2f& _position)
{
	if (slot)
	{
		slot->SetPosition(slot->GetParent()->GetPosition() + _position);
		Super::SetPosition(slot->GetPosition());
		image->SetPosition(slot->GetPosition());
	}
	else
	{
		Super::SetPosition(_position);
		image->SetPosition(_position);
	}
}

void UI::ImageWidget::UpdateSize(const Vector2f& _size)
{
	if (slot)
	{
		slot->SetSize(Vector2f(slot->GetParent()->GetScale().x * _size.x, slot->GetParent()->GetScale().y * _size.y));
		SetScale(Vector2f(slot->GetSize().x / initialSize.x, slot->GetSize().y / initialSize.y));
	}
	else
	{
		SetScale(Vector2f(_size.x / initialSize.x, _size.y / initialSize.y));
	}
}

void UI::ImageWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	_window.draw(*image->GetMesh()->GetShape()->GetDrawable());
	_window.draw(gradient);
}

void UI::ImageWidget::SetSizeToContent(const bool _fillToContent)
{
	if (_fillToContent)
	{
		initialSize = GetSize();
		SetSize(slot->GetSize());
	}
	else
	{
		SetSize(initialSize);
	}
}

void UI::ImageWidget::SetGradient(const Gradient& _gradient)
{
	colorGradient = _gradient;
	UpdateGradient();
}
