#include "ButtonWidget.h"
#include "Level.h"

using namespace Input;

UI::ButtonWidget::ButtonWidget(Level* _level, const RectangleShapeData& _data, const string _name, const RenderType& _renderType)
							 : ImageWidget(_level, _data, _name, _renderType)
{
	isPressed = false;
	isHovered = false;
	callbackData = make_unique<CallbackData>();
	inputManager = nullptr;
}


void UI::ButtonWidget::OnClick()
{
	if (visibility == Hidden) return;
	for (function<void()>& _action : callbackData.get()->onClickActions)
	{
		_action();
	}
}

void UI::ButtonWidget::OnRelease()
{
	if (visibility == Hidden) return;
	for (function<void()>& _action : callbackData.get()->onRealeaseActions)
	{
		_action();
	}
}

void UI::ButtonWidget::OnHover()
{
	if (visibility == Hidden) return;
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
	if (visibility == Hidden) return;
	for (function<void()>& _action : callbackData.get()->onUnhoversActions)
	{
		_action();
	}
}

void UI::ButtonWidget::OnDrag(const Vector2f& _mousePosition)
{
	if (!isPressed || visibility == Hidden) return;

	for (function<void(const Vector2f&)>& _action : callbackData.get()->onDragActions)
	{
		_action(_mousePosition);
	}
}

void UI::ButtonWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	Super::Render(_window);
}

void UI::ButtonWidget::BindActions(Input::InputManager& _inputManager)
{
	const string& _name = GetName();
	LOG(Display, _name);
	ActionMap* _actionMap = _inputManager.CreateActionMap("UI_" + _name);

	_actionMap->AddAction("OnClick_" + _name, ActionData(MouseButtonPressed, Mouse::Button::Left), [&]()
	{
		if (isHovered)
		{
			isPressed = true;
			OnClick();
		}
	});
		
	_actionMap->AddAction("OnRealeased_" + _name, ActionData(MouseButtonReleased, Mouse::Button::Left), [&]()
	{
		if (isPressed)
		{
			OnRelease();
		}
		isPressed = false;
	});
		
	_actionMap->AddAction("OnHover_" + _name, MouseMoved, [&](const Vector2f& _mousePosition)
	{
		if (GetGlobalBox().contains(_mousePosition))
		{
			if (!isHovered)
			{
				OnHover();
				isHovered = true;
			}
		}
		else
		{
			if (isHovered)
			{
				OnUnhover();
			}
			isHovered = false;
		}
	});
		
	_actionMap->AddAction("OnDrag_" + _name, MouseMoved, [&](const Vector2f& _mousePosition)
	{
		if (isPressed)
		{
			OnDrag(_mousePosition);
		}
	});
		
	_actionMap->Enable();
}