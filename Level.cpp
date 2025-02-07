#include "Level.h"
#include "LevelManager.h"
#include "ImageWidget.h"

Level::Level(const string& _name)
{
	isLoaded = false;
	window.create(VideoMode({ 1200, 600 }), _name);
	window.setVisible(false);
	name = _name;
	actorManager = ActorManager();
	cameraManager = CameraManager();
	audioManager = AudioManager();
	gameModeRef = GameMode(this);
	gameMode = nullptr;

	M_LEVEL.RegisterLevel(_name, this);
}


void Level::Update(const float _deltaTime)
{
	actorManager.Update(_deltaTime);
	//TODO change
	GetGameMode()->GetPlayerController()->GetInputManager().Update(window);

	if (!window.isOpen())
	{
		M_LEVEL.SetLevel(nullptr);
	}
}

void Level::UpdateWindow()
{
	window.clear();
	cameraManager.RenderAllCameras(window);
	window.display();
}

void Level::Load()
{
	if (!isLoaded)
	{
		InitLevel();
	}

	window.setVisible(true);
}

void Level::Unload()
{
	window.setVisible(false);
	window.clear();
}

void Level::InitLevel()
{
	isLoaded = true;
	ImageWidget* _widget = SpawnWidget<ImageWidget>(RectangleShapeData(Vector2f(800.0f, 600.0f)));
	GetHUD()->AddToViewport(_widget);
}