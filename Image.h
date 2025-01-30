#pragma once
#include "Widget.h"
#include "ShapeObject.h"

namespace UI
{
	class Image : public Widget
	{
		ShapeObject* image;

		bool sizeToContent;
		Vector2f initialSize;

	public:
		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			Super::SetPosition(_position);
			image->SetPosition(_position);
		}
		FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
		{
			Super::SetRotation(_rotation);
			image->SetRotation(_rotation);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			image->SetScale(_scale);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
			image->SetOrigin(_origin);
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			image->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			image->Rotate(_angle);
		}
		FORCEINLINE virtual void Scale(const Vector2f& _factor) override
		{
			Super::Scale(_factor);
			image->Scale(_factor);
		}
		FORCEINLINE virtual void SetFillColor(const Color& _color)
		{
			image->GetDrawable()->setFillColor(_color);
		}
		FORCEINLINE Vector2f GetSize() const
		{
			return image->GetDrawable()->getScale();
		}
		FORCEINLINE Vector2f GetPosition() const
		{
			return image->GetDrawable()->getPosition();
		}


	public:
		Image(const string& _name, const RectangleShapeData& _data, const RenderType& _type = Screen);

	private:
		void UpdateSize();

	public:
		virtual void Render(RenderWindow& _window) override;
	};
}
