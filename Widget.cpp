#include "Widget.h"
#include "CameraManager.h"
#include "Level.h"

using namespace Camera;
using namespace Input;

UI::Widget::Widget(Level* _level, const string& _name, const RenderType& _type) : Actor(_level, _name)
{
	type = _type;
	visibility = Visible;
	renderToken = 0;
	slot = nullptr;
	hud = _level->GetGameMode()->GetHUD();
}

UI::Widget::~Widget()
{
	delete slot;
}

void UI::Widget::Construct()
{
	Super::Construct();

	if (PlayerController* _playerController = GetLevel()->GetGameMode()->GetPlayerController<PlayerController>())
	{
		InputManager& _inputManager = _playerController->GetInputManager();
		BindActions(_inputManager);
	}
}

void UI::Widget::BindViewport()
{
	for (Actor* _actor : GetChildren())
	{
		if (Widget* _widget = Cast<Widget>(_actor))
		{
			_widget->BindViewport();
		}
	}
	const RenderData& _data = RenderData(bind(&Widget::Render, this, _1), type);
	renderToken = level->GetCameraManager().BindOnRenderWindow(_data, zOrder);
}

void UI::Widget::UnbindViewport()
{
	level->GetCameraManager().UnbindOnRenderWindow(renderToken);
}

void UI::Widget::SetZOrder(const int _zOrder)
{
	Super::SetZOrder(_zOrder);

	level->GetCameraManager().SetZOrder(renderToken, _zOrder);
}