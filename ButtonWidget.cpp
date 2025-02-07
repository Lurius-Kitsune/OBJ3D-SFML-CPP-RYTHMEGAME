#include "ButtonWidget.h"
#include "HUD.h"

UI::ButtonWidget::ButtonWidget(const string _name, const RectangleShapeData& _data, const RenderType& _renderType)
	: ImageWidget(_name, _data, _renderType)
{
	callbackData = make_unique<CallbackData>();
	isHovered = false;
	isPressed = false;
}

UI::ButtonWidget::~ButtonWidget()
{
}

void UI::ButtonWidget::OnClick()
{
	for (function<void()>& _action : callbackData.get()->onClickActions)
	{
		_action();
	}
}

void UI::ButtonWidget::OnRelease()
{
	for (function<void()>& _action : callbackData.get()->onRealeaseActions)
	{
		_action();
	}
}

void UI::ButtonWidget::OnHover()
{
	if (!isHovered)
	{
		for (function<void()>& _action : callbackData.get()->onHoverActions)
		{
			_action();
		}
	}
}

void UI::ButtonWidget::OnUnhover()
{
	for (function<void()>& _action : callbackData.get()->onUnhoversActions)
	{
		_action();
	}
}

void UI::ButtonWidget::OnDrag(const MouseMouvement* _mouseMovement)
{
	if(!isPressed) return;
	for (function<void(const MouseMouvement*)>& _action : callbackData.get()->onDragActions)
	{
		_action(_mouseMovement);
	}
}

void UI::ButtonWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	Super::Render(_window);
}
