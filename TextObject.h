#pragma once
#include "Object.h"

enum FontExtensionType
{
	OTF,
	TTF,
};

class TextObject : public Object
{
	Text* text;
	Font font;
	string path;
	FontExtensionType fontType;

public:
	FORCEINLINE Font& GetFont()
	{
		return font;
	}
	FORCEINLINE virtual Text* GetDrawable() const override
	{
		return text;
	}
	FORCEINLINE virtual void SetFillColor(const Color& _color) override
	{
		text->setFillColor(_color);
	}
	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
	{
		text->setOrigin(_origin);
	}
	FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
	{
		text->setPosition(_position);
	}
	FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
	{
		text->setRotation(_rotation);
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
	{
		text->setScale(_scale);
	}
	FORCEINLINE virtual void SetTransform(const TransformData& _transformData) override
	{
		text->setOrigin(_transformData.origin);
		text->setPosition(_transformData.position);
		text->setRotation(_transformData.rotation);
		text->setScale(_transformData.scale);
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset) override
	{
		text->move(_offset);
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle) override
	{
		text->rotate(_angle);
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor) override
	{
		text->scale(_factor);
	}

	FORCEINLINE void SetString(const string& _string)
	{
		text->setString(_string);
	}

public:
	TextObject(const string& _text, const string& _path = "", const FontExtensionType& _fontType = OTF);
	TextObject(const TextObject& _other);
	~TextObject();
};