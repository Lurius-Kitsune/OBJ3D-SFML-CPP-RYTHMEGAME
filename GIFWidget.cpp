#include "GIFWidget.h"

UI::GIFWidget::GIFWidget(Level* _level, const RectangleShapeData& _data, const string& _name, const RenderType& _type)
					   : ImageWidget(_level, _data, _name, _type)
{
	animation = CreateComponent<AnimationComponent>();
}

UI::GIFWidget::GIFWidget(Level* _level, const CircleShapeData& _data, const string& _name, const RenderType& _type)
					   : ImageWidget(_level, _data, _name, _type)
{
	animation = CreateComponent<AnimationComponent>();
}

UI::GIFWidget::GIFWidget(const GIFWidget& _other) : ImageWidget(_other)
{
	animation = _other.animation;
}


void UI::GIFWidget::BeginPlay()
{
	Super::BeginPlay();

	animation->StartAnimation();
}