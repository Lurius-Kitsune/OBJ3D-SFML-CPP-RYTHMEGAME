#pragma once
#include "Widget.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"

namespace UI
{
	class SliderWidget : public Widget
	{
		float value;
		float minValue;
		float maxValue;
		float step;
		ImageWidget* sliderBar;
		ButtonWidget* sliderButton;

	public:
		#pragma region Modifier
		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			Super::SetPosition(_position);
			const Vector2f& _origin = GetOrigin();
			sliderBar->SetPosition(_position - _origin);
			sliderButton->SetPosition(_position - _origin);
			UpdateCursorPosition();
		}
		FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
		{
			Super::SetRotation(_rotation);
			sliderBar->SetRotation(_rotation);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			sliderBar->SetScale(_scale);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
		}
		FORCEINLINE void SetOriginAtMiddle()
		{
			SetOrigin(sliderBar->GetMeshActor()->GetMesh()->GetShape()->GetDrawable()->getGeometricCenter());
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			sliderBar->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			sliderBar->Rotate(_angle);
		}
		FORCEINLINE virtual void Scale(const Vector2f& _factor) override
		{
			Super::Scale(_factor);
			sliderBar->Scale(_factor);
		}
		#pragma endregion

		#pragma region SliderSettings
		FORCEINLINE void SetValue(const float _value)
		{
			value = _value >= minValue ? _value <= maxValue ? _value : maxValue : minValue;
		}
		FORCEINLINE void AddValue(const float _value)
		{
			SetValue(value + _value);
		}
		FORCEINLINE void SetMinValue(const float _minValue)
		{
			if (_minValue > maxValue)
			{
				maxValue = _minValue;
				SetMaxValue(_minValue);
				return;
			}
			else
			{
				minValue = _minValue;
			}
			SetValue(value);
		}
		FORCEINLINE void SetMaxValue(const float _maxValue)
		{
			if (_maxValue < minValue)
			{
				minValue = _maxValue;
				SetMinValue(_maxValue);
				return;
			}
			else
			{
				maxValue = _maxValue;
			}
			SetValue(value);
		}
		FORCEINLINE void SetStep(const float _step)
		{
			step = _step < 1.0f ? 1.0f : _step;
		}
		FORCEINLINE float GetValue() const
		{
			return value;
		}
		#pragma endregion

		FORCEINLINE ButtonWidget* GetButton() const
		{
			return sliderButton;
		}
		
	public:

		SliderWidget(const string _name, const RenderType& _renderType);

	public:
		virtual void Render(RenderWindow& _window) override;

	private: 
		void Init();

		void UpdateCursorPosition();

	};
}

