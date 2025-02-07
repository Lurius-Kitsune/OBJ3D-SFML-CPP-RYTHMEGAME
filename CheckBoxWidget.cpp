#include "CheckBoxWidget.h"
#include "Level.h"

UI::CheckBoxWidget::CheckBoxWidget(Level* _level, const string& _name, const float _size, const RenderType& _type)
								 : ButtonWidget(_level, _name, RectangleShapeData(Vector2f(_size, _size), ""), _type)
{
	isChecked = false;
	checkImage = level->SpawnWidget<ImageWidget>("CheckImage", RectangleShapeData(Vector2f(_size, _size), "CheckMark"), _type);
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