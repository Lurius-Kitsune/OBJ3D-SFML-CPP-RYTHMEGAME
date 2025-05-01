#include "FloatingLabelWidget.h"
#include "TimerManager.h"

UI::FloatingLabelWidget::FloatingLabelWidget(Level* _level, const string& _text, const string& _name, const RenderType& _type)
	: LabelWidget(_level, _text, _name, _type)
{
}



void UI::FloatingLabelWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;

	const float _deltatime = M_TIMER.GetDeltaTime().asSeconds();
	const Vector2f& _currentposition = GetPosition();
	const Vector2f _targetPosition = _currentposition + Vector2f(0, moveSpeed* _deltatime);
	SetPosition(_targetPosition);

	// Fading
	if (GetFillColor().a > 0)
	{
		const Color& _currentColor = GetFillColor();
		SetFillColor(Color(_currentColor.r, _currentColor.g, _currentColor.b, _currentColor.a - fadeSpeed * _deltatime));
	}

	Super::Render(_window);
}
