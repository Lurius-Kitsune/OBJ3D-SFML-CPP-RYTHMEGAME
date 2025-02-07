#include "ImageWidget.h"
#include "Level.h"
#include "TextureManager.h"

#include "PanelWidget.h"

UI::ImageWidget::ImageWidget(Level* _level, const RectangleShapeData& _data, const string& _name, const RenderType& _type)
						   : Widget(_level, _name, _type)
{
	image = level->SpawnActor<MeshActor>(_data, _name);
	sizeToContent = false;
	initialSize = GetSize();
	gradient = VertexArray();
	colorGradient = Gradient();
	SetTexture(_data.path);
}

UI::ImageWidget::ImageWidget(Level* _level, const CircleShapeData& _data, const string& _name, const RenderType& _type)
						   : Widget(_level, _name, _type)
{
	image = level->SpawnActor<MeshActor>(_data, _name);
	sizeToContent = false;
	initialSize = GetSize();
	gradient = VertexArray();
	colorGradient = Gradient();
	SetTexture(_data.path);
}

UI::ImageWidget::ImageWidget(const ImageWidget& _other) : Widget(_other)
{
	sizeToContent = _other.sizeToContent;
	initialSize = _other.initialSize;
	gradient = _other.gradient;
	colorGradient = _other.colorGradient;

	const ShapeObjectData& _data = _other.image->GetMesh()->GetShape()->GetData();
	const ShapeObjectType& _type = _data.type;

	if (_type == SOT_CIRCLE)
	{
		const CircleShapeData* _circleData = _data.data.circleData;
		image = level->SpawnActor<MeshActor>(*_circleData, _other.GetName());
		SetTexture(_circleData->path);
	}

	else if (_type == SOT_RECTANGLE)
	{
		const RectangleShapeData* _rectangleData = _data.data.rectangleData;
		image = level->SpawnActor<MeshActor>(*_rectangleData, _other.GetName());
		SetTexture(_rectangleData->path);
	}

	else
	{
		image = nullptr;
		LOG(Fatal, "Alors oui, euh.. Bah c'était pas censé arriver..");
	}
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

void UI::ImageWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;

	_window.draw(*image->GetMesh()->GetShape()->GetDrawable());
	_window.draw(gradient);
}