#include "SliderWidget.h"
#include "HUD.h"

UI::SliderWidget::SliderWidget(const string _name, const RenderType& _renderType)
	: Widget(_name, _renderType)
{
	minValue = 0.0f;
	value = 0.0f;
	maxValue = 100.0f;
	step = 1.0f;
	sliderBar = M_HUD.CreateWidget<ImageWidget>(_name+"Bar", RectangleShapeData(Vector2f(100.0f, 10.0f), "sliderBar"), _renderType);
	sliderButton = M_HUD.CreateWidget<ButtonWidget>(_name+"Button", RectangleShapeData(Vector2f(10.0f, 25.0f), "sliderButton"), _renderType);
	Init();
}

void UI::SliderWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	sliderBar->Render(_window);
	sliderButton->Render(_window);
}

void UI::SliderWidget::Init()
{
	sliderButton->SetOriginAtMiddle();
	sliderButton->SetTexture("");
	UpdateCursorPosition();

	//Bind
	sliderButton->BindOnDragAction([&] (const MouseMouvement* _mouseMovement) {
		const Vector2i& _mousePosition = _mouseMovement->position;
		const Vector2f& _position = sliderBar->GetPosition();
		const Vector2f& _size = sliderBar->GetSize();
		const float _normaliseValue = (_mousePosition.x - _position.x) / _size.x;
		const float _value = minValue + (_normaliseValue * (maxValue - minValue));
		// Use step and get a float
		const float _stepValue = round(_value / step) * step;
		SetValue(_stepValue);
		UpdateCursorPosition();
		LOG(Display, "Value : " + to_string(value));
	});
}

void UI::SliderWidget::UpdateCursorPosition()
{
	const Vector2f& _position = sliderBar->GetPosition();
	// Normalise la value
	const float _normaliseValue = (value - minValue) / (maxValue - minValue);
	const Vector2f& _offset = Vector2f(sliderBar->GetSize().x * _normaliseValue, sliderBar->GetSize().y / 2.0f);
	sliderButton->SetPosition(_position + _offset);
}
