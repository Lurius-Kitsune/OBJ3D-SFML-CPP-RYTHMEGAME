#include "LabelWidget.h"

UI::LabelWidget::LabelWidget(Level* _level, const string& _text, const string& _name, const RenderType& _type) : Widget(_level, _name, _type)
{
	text = new TextObject(_text, "Default", OTF);
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
	if (slot && slot->GetDebugMode())
	{
		slot->RenderDebugFrame(_window);
	}
}

void UI::LabelWidget::UpdatePosition(const Vector2f _position)
{
	if (slot)
	{
		slot->SetPosition(_position);
		Super::SetPosition(slot->GetPosition());
		text->SetPosition(_position);
	}
	else
	{
		Super::SetPosition(_position);
		text->SetPosition(_position);
	}
}

void UI::LabelWidget::UpdateMove(const Vector2f& _offset)
{
	if (slot)
	{
		slot->SetPosition(GetPosition());
		Super::Move(_offset);
		text->Move(_offset);
	}

	else
	{
		Super::Move(_offset);
		text->Move(_offset);
	}
}