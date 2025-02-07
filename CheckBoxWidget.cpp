#include "CheckBoxWidget.h"
#include "HUD.h"

UI::CheckBoxWidget::CheckBoxWidget(const string& _name, const float _size, const RenderType& _type)
	: ButtonWidget(_name, RectangleShapeData(Vector2f(_size, _size), ""), _type)
{
	isChecked = false;
	checkImage = M_HUD.CreateWidget<ImageWidget>("CheckImage", RectangleShapeData(Vector2f(_size, _size), "checkmark"), _type);
	checkImage->SetZOrder(zOrder + 1);
}

void UI::CheckBoxWidget::OnClick()
{
	Super::OnClick();
	isChecked = !isChecked;
}

void UI::CheckBoxWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	Super::Render(_window);
	if(isChecked) checkImage->Render(_window);
}
