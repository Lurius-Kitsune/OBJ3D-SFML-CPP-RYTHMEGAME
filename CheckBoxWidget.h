#pragma once
#include "ButtonWidget.h"

namespace UI
{
	class CheckBoxWidget : public ButtonWidget
	{
		bool isChecked;
		ImageWidget* checkImage;

	public:
		#pragma region Modifier
		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			Super::SetPosition(_position);
			checkImage->SetPosition(_position);
		}
		FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
		{
			Super::SetRotation(_rotation);
			checkImage->SetRotation(_rotation);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			checkImage->SetScale(_scale);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
			checkImage->SetOrigin(_origin);
		}
		FORCEINLINE virtual void SetOriginAtMiddle()
		{
			SetOrigin(image->GetMesh()->GetShape()->GetDrawable()->getGeometricCenter());
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			checkImage->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			checkImage->Rotate(_angle);
		}
		FORCEINLINE virtual void Scale(const Vector2f& _factor) override
		{
			Super::Scale(_factor);
			checkImage->Scale(_factor);
		}
		#pragma endregion
		FORCEINLINE virtual bool GetIsChecked() const
		{
			return isChecked;
		}
		FORCEINLINE void SetIsChecked(const bool _isChecked)
		{
			isChecked = _isChecked;
		}

		FORCEINLINE virtual void SetZOrder(const int _zOrder) override
		{
			Super::SetZOrder(_zOrder);
			checkImage->SetZOrder(_zOrder+1);
		}
		FORCEINLINE virtual ImageWidget* GetCheckImage() const
		{
			return checkImage;
		}
		FORCEINLINE virtual void SetCheckTexture(const string& _texture, const TextureExtensionType& _extension = PNG)
		{
			checkImage->SetTexture(_texture, _extension);
		}
	public:
		CheckBoxWidget(const string& _name, const float _size, const RenderType& _type = Screen);
	
	public:
		virtual void OnClick() override;
		virtual void Render(RenderWindow& _window) override;
	};
}


