#include "LabelWidget.h"
#include "CameraManager.h"

UI::LabelWidget::LabelWidget(const string& _text, const string& _name, const RenderType& _type) : Widget(_name, _type)
{
	text = new TextObject(_text, "");
}

UI::LabelWidget::~LabelWidget()
{
	delete text;
}


void UI::LabelWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	_window.draw(*text->GetDrawable());
}

void UI::LabelWidget::Tick(const float _deltaTime)
{
	
}

string UI::LabelWidget::ComputeScoreText()
{
	stringstream _ss;
	_ss << setw(scoreMaxDigit) << setfill('0') << score;

	return _ss.str();
}
