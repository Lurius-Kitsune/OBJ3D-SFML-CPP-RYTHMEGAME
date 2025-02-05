#include "Label.h"
#include "CameraManager.h"

UI::Label::Label(const string& _text, const RenderType& _type, const string& _path,
				 const FontExtensionType& _fontType)
			   : Widget("Label", _type)
{
	text = new TextObject(_text, _path, _fontType);
}

UI::Label::~Label()
{
	delete text;
}


void UI::Label::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	_window.draw(*text->GetDrawable());
}