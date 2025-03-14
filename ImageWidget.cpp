#include "ImageWidget.h"
#include "Level.h"
#include "TextureManager.h"

#include "PanelWidget.h"

UI::ImageWidget::ImageWidget(Level* _level, const RectangleShapeData& _data, const string& _name, const RenderType& _type)
						   : Widget(_level, _name, _type)
{
	sizeToContent = false;
	image = CreateComponent<MeshComponent>(_data);
	initialSize = GetSize();
	gradient = VertexArray(PrimitiveType::TriangleStrip, 4);
	colorGradient = ImageGradient();
	useGradient = false;
}

UI::ImageWidget::ImageWidget(Level* _level, const CircleShapeData& _data, const string& _name, const RenderType& _type)
						   : Widget(_level, _name, _type)
{
	sizeToContent = false;
	image = CreateComponent<MeshComponent>(_data);
	initialSize = GetSize();
	gradient = VertexArray(PrimitiveType::TriangleStrip, 4);
	colorGradient = ImageGradient();
	useGradient = false;
}

UI::ImageWidget::ImageWidget(const ImageWidget& _other) : Widget(_other)
{
	sizeToContent = _other.sizeToContent;
	initialSize = _other.initialSize;
	gradient = _other.gradient;
	colorGradient = _other.colorGradient;
	useGradient = _other.useGradient;

	const ShapeObjectData& _data = _other.image->GetShape()->GetData();
	const ShapeObjectType& _type = _data.type;

	if (_type == SOT_CIRCLE)
	{
		const CircleShapeData* _circleData = _data.data.circleData;
		image = CreateComponent<MeshComponent>(*_circleData);
		SetTexture(_circleData->path);
	}

	else if (_type == SOT_RECTANGLE)
	{
		const RectangleShapeData* _rectangleData = _data.data.rectangleData;
		image = CreateComponent<MeshComponent>(*_rectangleData);
		SetTexture(_rectangleData->path);
	}

	else
	{
		image = nullptr;
		LOG(Fatal, "Alors oui, euh.. Bah c'était pas censé arriver..");
	}
	image->Deconstruct();
}


void UI::ImageWidget::UpdateGradient()
{
	if (slot)
	{
		gradient[0].position = slot->GetPosition();
		gradient[0].color = colorGradient.topLeft;

		gradient[1].position = { slot->GetPosition().x + slot->GetSize().x, slot->GetPosition().y };
		gradient[1].color = colorGradient.topRight;

		gradient[2].position = { slot->GetPosition().x, slot->GetPosition().y + slot->GetSize().y };
		gradient[2].color = colorGradient.bottomLeft;

		gradient[3].position = slot->GetPosition() + slot->GetSize();
		gradient[3].color = colorGradient.bottomRight;
	}
	else
	{
		gradient[0].position = GetPosition();
		gradient[0].color = colorGradient.topLeft;

		gradient[1].position = { GetPosition().x + GetSize().x, GetPosition().y };
		gradient[1].color = colorGradient.topRight;

		gradient[2].position = { GetPosition().x, GetPosition().y + GetSize().y };
		gradient[2].color = colorGradient.bottomLeft;

		gradient[3].position = GetPosition() + GetSize();
		gradient[3].color = colorGradient.bottomRight;
	}
	
}

void UI::ImageWidget::UpdatePosition(const Vector2f& _position)
{
	if (slot)
	{
		slot->SetPosition(_position);
		Super::SetPosition(slot->GetPosition());
		image->GetShape()->SetPosition(_position);
	}

	else
	{
		Super::SetPosition(_position);
		image->GetShape()->SetPosition(_position);
	}
	UpdateGradient();
}

void UI::ImageWidget::UpdateMove(const Vector2f& _offset)
{
	if (slot)
	{
		slot->SetPosition(GetPosition());
		Super::Move(_offset);
		image->GetShape()->Move(_offset);
	}

	else
	{
		Super::Move(_offset);
		image->GetShape()->Move(_offset);
	}
	UpdateGradient();
}

void UI::ImageWidget::UpdateSize(const Vector2f& _size)
{
	if (slot)
	{
		slot->SetSize(Vector2f(slot->GetParent()->GetScale().x * _size.x, slot->GetParent()->GetScale().y * _size.y));
		image->GetShape()->SetScale(Vector2f(slot->GetSize().x / initialSize.x, slot->GetSize().y / initialSize.y));
	}

	else
	{
		image->GetShape()->SetScale(Vector2f(_size.x / initialSize.x, _size.y / initialSize.y));
	}
	UpdateGradient();
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
	UpdateGradient();
}

void UI::ImageWidget::SetGradient(const ImageGradient& _gradient)
{
	colorGradient = _gradient;
	useGradient = true;
	UpdateGradient();
}

void UI::ImageWidget::SetGradient(const bool _useGradient)
{
	useGradient = _useGradient;
}

void UI::ImageWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;

	image->RenderMesh(_window);
	if (useGradient) _window.draw(gradient);

	if (slot && slot->GetDebugMode())
	{
		slot->RenderDebugFrame(_window);
	}
}