#pragma once
#include "ImageWidget.h"

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
	class ProgressBarWidget : public ImageWidget
	{
		ProgressType type;
		ImageWidget* foreground;
		float currentValue;
		float maxValue;
		Vector2f size;

	public:
		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			Super::SetPosition(_position);
			UpdateOriginAndPosition(size);
		}
		FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
		{
			Super::SetRotation(_rotation);
			foreground->SetRotation(_rotation);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			foreground->SetScale(_scale);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
			foreground->SetOrigin(_origin);
			
			UpdateOriginAndPosition(size);
		}
		FORCEINLINE virtual void SetOriginAtMiddle()
		{
			Super::SetOriginAtMiddle();
			foreground->SetOriginAtMiddle();
			UpdateOriginAndPosition(size);
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			foreground->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			foreground->Rotate(_angle);
		}
		FORCEINLINE virtual void Scale(const Vector2f& _factor) override
		{
			Super::Scale(_factor);
			foreground->Scale(_factor);
		}
		FORCEINLINE virtual void SetVisibility(const VisibilityType& _visibility)
		{
			Super::SetVisibility(_visibility);
			foreground->SetVisibility(_visibility);
		}
		FORCEINLINE virtual void SetZOrder(const int _zOrder)
		{
			Super::SetZOrder(_zOrder);
			foreground->SetZOrder(_zOrder+1);
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
		FORCEINLINE ImageWidget* GetForeground() const
		{
			return foreground;
		}

	public:
		ProgressBarWidget(const ProgressType& _type, const RectangleShapeData& _data,
			const string _name, const float _maxValue = 100.0f,
			const RenderType& _renderType = Screen);
		virtual ~ProgressBarWidget();

	public:
		virtual void Render(RenderWindow& _window) override;

	private:
		void Update();
		void UpdateOriginAndPosition(const Vector2f& _size);
		IntRect MakeRect(const float _percent);
};
}