#pragma once
#include "Widget.h"
#include "TextObject.h"
#include "FontManager.h"

namespace UI
{
	class LabelWidget : public Widget
	{
		TextObject* text;
		u_int score;
		u_int scoreMaxDigit;

	public:
	#pragma region Modifier

		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			Super::SetPosition(_position);
			text->SetPosition(_position);
		}
		FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
		{
			Super::SetRotation(_rotation);
			text->SetRotation(_rotation);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			text->SetScale(_scale);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
			text->SetOrigin(_origin);
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			text->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			text->Rotate(_angle);
		}
		FORCEINLINE virtual void Scale(const Vector2f& _factor) override
		{
			Super::Scale(_factor);
			text->Scale(_factor);
		}
		FORCEINLINE virtual void SetOriginAtMiddle()
		{
			SetOrigin(text->GetDrawable()->getLocalBounds().getCenter());
		}

	#pragma endregion

	#pragma region Setter

		FORCEINLINE virtual void SetText(const string& _text)
		{
			text->GetDrawable()->setString(_text);
		}
		FORCEINLINE virtual void SetCharacterSize(const u_int& _value)
		{
			text->GetDrawable()->setCharacterSize(_value);
		}
		FORCEINLINE virtual void SetFillColor(const Color& _color)
		{
			text->GetDrawable()->setFillColor(_color);
		}
		FORCEINLINE virtual void SetTransparency(const u_int& _alpha)
		{
			text->GetDrawable()->setFillColor(Color(GetFillColor().r, GetFillColor().g, GetFillColor().b, _alpha));
		}
		//Info : Update Origin to fix potential height issue because of the Font
		FORCEINLINE virtual void SetFont(const string& _path, const FontExtensionType& _fontType)
		{
			M_FONT.Load(text, _path, _fontType);
		}

	#pragma endregion

	#pragma region Getter
		FORCEINLINE virtual Color GetFillColor() const
		{
			return text->GetDrawable()->getFillColor();
		}
		FORCEINLINE virtual Vector2f GetSize() const override
		{
			return text->GetDrawable()->getLocalBounds().size;
		}
	#pragma endregion


	public:
		LabelWidget(const string& _text, const string& _name, const RenderType& _type = Screen);
		~LabelWidget();

	public:
		virtual void Render(RenderWindow& _window) override;
		virtual void Tick(const float _deltaTime) override;

	private:
		string ComputeScoreText();
	};
}