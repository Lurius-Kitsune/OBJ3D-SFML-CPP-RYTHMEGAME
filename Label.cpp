#include "Label.h"
#include "CameraManager.h"

Label::Label(const string& _text, const string& _path, const FontExtensionType& _fontType) : Actor("Label")
{
	text = new TextObject(_text, _path, _fontType);

	textMeshToken = -1;
}

Label::Label(const Label& _other) : Actor(_other)
{
	text = new TextObject(*_other.text);
	textMeshToken = -1;
}

Label::~Label()
{
	delete text;
}


void Label::Construct()
{
	Super::Construct();
	textMeshToken = M_CAMERA.BindOnRenderWindow(bind(&Label::RenderText, this, placeholders::_1));
}

void Label::Deconstruct()
{
	Super::Deconstruct();
	M_CAMERA.UnbindOnRenderWindow(textMeshToken);
}


void Label::RenderText(RenderWindow& _window)
{
	_window.draw(*text->GetDrawable());
}