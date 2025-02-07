#include "LabelWidget.h"

UI::LabelWidget::LabelWidget(Level* _level, const string& _text, const string& _name, const RenderType& _type) : Widget(_level, _name, _type)
{
	text = new TextObject(_text, "");
}

UI::LabelWidget::~LabelWidget()
{
	delete text;
}


string UI::LabelWidget::ComputeScoreText()
{
	stringstream _ss;
	_ss << setw(scoreMaxDigit) << setfill('0') << score;

	return _ss.str();
}


void UI::LabelWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	_window.draw(*text->GetDrawable());
}