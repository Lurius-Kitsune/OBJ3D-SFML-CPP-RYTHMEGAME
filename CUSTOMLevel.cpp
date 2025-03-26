#include "CUSTOMLevel.h"

#include "CUSTOMHUD.h"
#include "CUSTOMGameMode.h"
#include "CUSTOMLevel.h"
#include "CUSTOMMesh.h"
#include "CustomActor.h"

#include "GIFWidget.h"
#include "Particle.h"
#include "LevelManager.h"
#include "CUSTOMPlayerController.h"
#include "CUSTOMPawn.h"
#include "SliderWidget.h"
#include "CheckBoxWidget.h"
#include "PlayerController.h"

CUSTOMLevel::CUSTOMLevel(const string& _name) : Level(_name)
{
	canvas = nullptr;
	image = nullptr;
	label = nullptr;
}


void CUSTOMLevel::InitLevel()
{
	Super::InitLevel();

	HUD* _hud = GetGameMode()->GetHUD();

	canvas = _hud->SpawnWidget<CanvasWidget>();
	canvas->SetDebugMode(true);
	canvas->SetSize(CAST(Vector2f, GetWindowSize()));

	GIFWidget* _gif = _hud->SpawnWidget<GIFWidget>(RectangleShapeData(GetWindowSize(), "SpriteSheet_Main_Menu_Loop"));
	canvas->AddChild(_gif);
	_gif->SetZOrder(0);

	vector<SpriteData> _spriteMainMenuLoop;
	for (int _i = 2; _i < 18; _i++)
	{
		for (int _j = 0; _j < 18; _j++)
		{
			if (_i == 2 && _j < 14) continue;
			_spriteMainMenuLoop.push_back(SpriteData(Vector2i(_j * 640, _i * 360), Vector2i(640, 360)));
		}
	}
	Animation* _loopAnim = new Animation("MainMenu BackgroundLoop", _gif->GetComponent<MeshComponent>()->GetShape(), AnimationData(2.0f, _spriteMainMenuLoop, true, false));
	_gif->AddAnimation(_loopAnim);

	const Vector2i& _spriteSize = Vector2i(41, 39);
	const vector<SpriteData>& _spritesData =
	{
		SpriteData(Vector2i(0, 8), _spriteSize),
		SpriteData(Vector2i(43, 8), _spriteSize),
		SpriteData(Vector2i(85, 8), _spriteSize),
		SpriteData(Vector2i(127, 8), _spriteSize),
		SpriteData(Vector2i(0, 48), _spriteSize),
		SpriteData(Vector2i(43, 48), _spriteSize),
		SpriteData(Vector2i(85, 48), _spriteSize),
		SpriteData(Vector2i(127, 48), _spriteSize),
		SpriteData(Vector2i(0, 86), _spriteSize),
		SpriteData(Vector2i(43, 86), _spriteSize),
		SpriteData(Vector2i(85, 86), _spriteSize),
		SpriteData(Vector2i(127, 86), _spriteSize),
	};
	const AnimationData& _animationData = AnimationData(2.0f, _spritesData);
	Animation* _duckAnim = new Animation("Duck animation", _gif->GetComponent<MeshComponent>()->GetShape(), _animationData);
	_gif->AddAnimation(_duckAnim);

	_loopAnim->AddLinkedAnimation([]() {return true; }, _duckAnim);

	label = _hud->SpawnWidget<LabelWidget>("Demo");
	canvas->AddChild(label);
	label->SetPosition({ 350.0f, 200.0f });
	label->SetFont("Minecrafter", TTF);
	label->SetZOrder(10);

	for (Slot* _slot : canvas->GetSlots())
	{
		Widget* _content = _slot->GetContent();
		_slot->SetDebugMode(true);
	}

	SpawnActor<ParticleActor>(1000, 3.0f);

	GetGameMode()->GetHUD()->AddToViewport(canvas);
}