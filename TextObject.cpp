#include "TextObject.h"
#include "FontManager.h"

TextObject::TextObject(const string& _text, const string& _path, const FontExtensionType& _fontType)
{
	text = new Text(font, _text);
	path = _path;
	fontType = _fontType;
	M_FONT.Load(this, path, fontType);
}

TextObject::TextObject(const TextObject& _other)
{
	text = new Text(*_other.text);
	path = _other.path;
	fontType = _other.fontType;
	M_FONT.Load(this, path, fontType);
}

TextObject::~TextObject()
{
	delete text;
}