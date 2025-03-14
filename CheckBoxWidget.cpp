#include "CheckBoxWidget.h"
#include "Level.h"

UI::CheckBoxWidget::CheckBoxWidget(Level* _level, const float _size, const string& _name, const RenderType& _type)
								 : ButtonWidget(_level, RectangleShapeData(Vector2f(_size, _size), "White"), _name, _type)
{
	isChecked = false;
	checkImage = hud->SpawnWidget<ImageWidget>(RectangleShapeData(Vector2f(_size, _size), "CheckMark"), "CheckImage", _type);
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