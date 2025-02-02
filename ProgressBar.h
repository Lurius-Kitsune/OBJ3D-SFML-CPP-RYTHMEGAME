#pragma once
#include "Widget.h"
#include "ShapeObject.h"

enum ProgressType
{
	PT_CENTER,
	PT_LEFT,
	PT_TOP,
	PT_RIGHT,
	PT_BOTTOM,

	PT_COUNT
};

namespace UI
{
	class ProgressBar : public Widget
	{
		ProgressType type;
		ShapeObject* foreground;
		ShapeObject* bar;
		float currentValue;
		float maxValue;
		Vector2f size;

	public:
		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			Super::SetPosition(_position);
			foreground->SetPosition(_position);
			bar->SetPosition(_position);
		}
		FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
		{
			Super::SetRotation(_rotation);
			foreground->SetRotation(_rotation);
			bar->SetRotation(_rotation);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			foreground->SetScale(_scale);
			bar->SetScale(_scale);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
			foreground->SetOrigin(_origin);
			bar->SetOrigin(_origin);
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			foreground->Move(_offset);
			bar->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			foreground->Rotate(_angle);
			bar->Rotate(_angle);
		}
		FORCEINLINE virtual void Scale(const Vector2f& _factor) override
		{
			Super::Scale(_factor);
			foreground->Scale(_factor);
			bar->Scale(_factor);
		}
		FORCEINLINE virtual void SetFillColor(const Color& _color)
		{
			foreground->GetDrawable()->setFillColor(_color);
		}
		FORCEINLINE Vector2f GetSize() const
		{
			return Cast<RectangleShape>(bar->GetDrawable())->getSize();
		}
		FORCEINLINE Vector2f GetPosition() const
		{
			return foreground->GetDrawable()->getPosition();
		}
		FORCEINLINE void SetType(const ProgressType& _type)
		{
			type = _type;
			UpdateOriginAndPosition(size);
		}
		FORCEINLINE void SetValue(const float _newValue)
		{
			currentValue = _newValue > maxValue ? maxValue : _newValue < 0 ? 0 : _newValue;
			Update();
		}
		FORCEINLINE void ChangeValue(const float _byAmount)
		{
			const float _newValue = currentValue + _byAmount;
			currentValue = _newValue > maxValue ? maxValue : _newValue < 0 ? 0 : _newValue;
			Update();
		}
		FORCEINLINE void ResetValue()
		{
			currentValue = maxValue;
			Update();
		}
		FORCEINLINE void ChangeMaxValue(const float _factor)
		{
			maxValue += _factor;
			Update();
		}
		FORCEINLINE float GetCurrentValue() const
		{
			return currentValue;
		}
		FORCEINLINE float GetMaxValue() const
		{
			return maxValue;
		}
		FORCEINLINE ShapeObject* GetForeground() const
		{
			return foreground;
		}

	public:
		ProgressBar(const ProgressType& _type, const RectangleShapeData& _data,
			const string _name, const float _maxValue = 100.0f,
			const RenderType& _renderType = Screen);

	public:
		virtual void Render(RenderWindow& _window) override;

	private:
		void Update();
		void UpdateOriginAndPosition(const Vector2f& _size);
		IntRect MakeRect(const float _percent);
};
}